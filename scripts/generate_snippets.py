#!/usr/bin/env python3
"""Generate VS Code C++ snippets from snippets/manual.json and library/**/*.cpp.

Run from anywhere:
    python scripts/generate_snippets.py
    python scripts/generate_snippets.py --check

The script assumes it resides in <repository>/scripts/.
"""

import argparse
import json
import os
import re
import sys
import tempfile
from pathlib import Path


START = re.compile(r"^\s*//\s*cpp\.json from here\s*$")
END = re.compile(r"^\s*//\s*cpp\.json (?:to|till) here\s*$")
META = re.compile(r"^\s*//\s*(name|prefix|description):\s*(.*)$")
REPLACE = re.compile(r"[ \t]+//[ \t]*snippet-replace:[ \t]*(.*)$")


class GenerationError(Exception):
    pass


def read_utf8(path):
    try:
        return path.read_text(encoding="utf-8-sig")
    except (OSError, UnicodeError) as exc:
        raise GenerationError(f"{path}: UTF-8として読み込めません: {exc}") from exc


def json_no_duplicate_keys(pairs):
    result = {}
    for key, value in pairs:
        if key in result:
            raise GenerationError(f"manual.json: JSONキーが重複しています: {key!r}")
        result[key] = value
    return result


def check_entry(name, entry, origin):
    if not isinstance(name, str) or not name.strip():
        raise GenerationError(f"{origin}: name は空でない文字列にしてください")
    if not isinstance(entry, dict):
        raise GenerationError(f"{origin}: スニペット定義はオブジェクトにしてください")

    prefix = entry.get("prefix")
    if isinstance(prefix, str):
        prefixes = [prefix]
    elif isinstance(prefix, list) and prefix and all(isinstance(x, str) for x in prefix):
        prefixes = prefix
    else:
        raise GenerationError(f"{origin}: prefix は文字列か文字列配列にしてください")
    if any(not p.strip() for p in prefixes):
        raise GenerationError(f"{origin}: prefix に空文字列を指定できません")
    if len(set(prefixes)) != len(prefixes):
        raise GenerationError(f"{origin}: 同じ prefix が繰り返されています")

    body = entry.get("body")
    if not isinstance(body, str) and not (
        isinstance(body, list) and all(isinstance(line, str) for line in body)
    ):
        raise GenerationError(f"{origin}: body は文字列か文字列配列にしてください")
    if "description" in entry and not isinstance(entry["description"], str):
        raise GenerationError(f"{origin}: description は文字列にしてください")
    return prefixes


def get_metadata(lines, start_idx, path):
    """Read consecutive // name/prefix/description lines just above a start marker."""
    metadata = {}
    idx = start_idx - 1
    while idx >= 0:
        found = META.fullmatch(lines[idx])
        if not found:
            break
        key, value = found.groups()
        if key in metadata:
            raise GenerationError(f"{path}:{idx + 1}: {key} の指定が重複しています")
        metadata[key] = value.strip()
        idx -= 1

    for key in ("name", "prefix"):
        if not metadata.get(key):
            raise GenerationError(
                f"{path}:{start_idx + 1}: マーカー直前の // {key}: がありません"
            )
    return metadata


def rewrite_line(line, path, line_number):
    if "snippet-replace:" not in line:
        return line
    found = REPLACE.search(line)
    if not found or not line[: found.start()].strip():
        raise GenerationError(
            f"{path}:{line_number}: snippet-replace の形式が正しくありません"
        )
    replacement = found.group(1)
    if not replacement:
        raise GenerationError(f"{path}:{line_number}: 置換後のコードが空です")
    indent = re.match(r"[ \t]*", line).group(0)
    return indent + replacement


def read_snippets(path):
    lines = read_utf8(path).splitlines()
    entries = []
    start_idx = None
    for idx, line in enumerate(lines):
        if START.fullmatch(line):
            if start_idx is not None:
                raise GenerationError(
                    f"{path}:{idx + 1}: 閉じる前に次の開始マーカーがあります"
                )
            start_idx = idx
        elif END.fullmatch(line):
            if start_idx is None:
                raise GenerationError(f"{path}:{idx + 1}: 対応しない終了マーカーです")
            metadata = get_metadata(lines, start_idx, path)
            body = [
                rewrite_line(lines[i], path, i + 1)
                for i in range(start_idx + 1, idx)
            ]
            if not body or not any(line.strip() for line in body):
                raise GenerationError(f"{path}:{start_idx + 1}: スニペット本体が空です")
            entry = {"prefix": metadata["prefix"], "body": body}
            if "description" in metadata:
                entry["description"] = metadata["description"].replace(r"\n", "\n")
            entries.append((metadata["name"], entry, f"{path}:{start_idx + 1}"))
            start_idx = None
    if start_idx is not None:
        raise GenerationError(f"{path}:{start_idx + 1}: 終了マーカーがありません")
    return entries


def generate(root, library_path, manual_path):
    if not library_path.is_dir():
        raise GenerationError(f"ライブラリのフォルダーがありません: {library_path}")
    try:
        manual = json.loads(
            read_utf8(manual_path), object_pairs_hook=json_no_duplicate_keys
        )
    except json.JSONDecodeError as exc:
        raise GenerationError(f"{manual_path}: JSONが不正です: {exc}") from exc
    if not isinstance(manual, dict):
        raise GenerationError(f"{manual_path}: JSONの最上位はオブジェクトにしてください")

    entries = {}
    prefix_owner = {}

    def add(name, entry, origin):
        prefixes = check_entry(name, entry, origin)
        if name in entries:
            raise GenerationError(f"スニペット名 {name!r} が重複しています: {origin}")
        for prefix in prefixes:
            if prefix in prefix_owner:
                raise GenerationError(
                    f"prefix {prefix!r} が重複しています: "
                    f"{prefix_owner[prefix]} / {origin}"
                )
        entries[name] = entry
        for prefix in prefixes:
            prefix_owner[prefix] = origin

    for name, entry in manual.items():
        add(name, entry, f"{manual_path} ({name})")

    cpp_files = sorted(library_path.rglob("*.cpp"), key=lambda p: p.as_posix())
    if not cpp_files:
        raise GenerationError(f".cpp が見つかりません: {library_path}")
    auto_count = 0
    for path in cpp_files:
        for name, entry, origin in read_snippets(path):
            add(name, entry, origin)
            auto_count += 1

    return entries, len(manual), auto_count, len(cpp_files)


def path_from_root(root, value):
    path = Path(value)
    return path if path.is_absolute() else root / path


def main():
    parser = argparse.ArgumentParser(description=".cpp と manual.json から VS Code の cpp.json を生成します")
    parser.add_argument("--root", type=Path, help="リポジトリのルート（省略時はスクリプトの親の親）")
    parser.add_argument("--library", default="library", help=".cpp を検索するフォルダー")
    parser.add_argument("--manual", default="snippets/manual.json", help="手書きスニペットのJSON")
    parser.add_argument("--output", default="snippets/cpp.json", help="生成先JSON")
    parser.add_argument("--check", action="store_true", help="生成物が最新か確認するだけで書き込まない")
    args = parser.parse_args()

    root = (args.root or Path(__file__).resolve().parent.parent).resolve()
    library = path_from_root(root, args.library)
    manual = path_from_root(root, args.manual)
    output = path_from_root(root, args.output)

    try:
        if manual.resolve() == output.resolve():
            raise GenerationError("manual.json と出力先が同じです")
        entries, manual_count, auto_count, file_count = generate(root, library, manual)
        result = json.dumps(entries, ensure_ascii=False, indent=2) + "\n"
        if args.check:
            if not output.exists() or read_utf8(output) != result:
                raise GenerationError(f"{output} が未生成か、最新ではありません")
            print(f"OK: {output} は最新です（手書き {manual_count} + 自動 {auto_count}）")
            return 0
        if output.exists() and read_utf8(output) == result:
            print(f"変更なし: {output}（手書き {manual_count} + 自動 {auto_count}）")
            return 0
        output.parent.mkdir(parents=True, exist_ok=True)
        # Validation is finished before writing. Replace the output atomically.
        with tempfile.NamedTemporaryFile(
            mode="w", encoding="utf-8", newline="\n", delete=False,
            dir=output.parent, prefix=".cpp.json.", suffix=".tmp"
        ) as stream:
            temp_path = Path(stream.name)
            stream.write(result)
        try:
            os.replace(temp_path, output)
        finally:
            temp_path.unlink(missing_ok=True)
        print(
            f"生成完了: {output}\n"
            f"  manual.json: {manual_count} 件\n"
            f"  .cpp から: {auto_count} 件（{file_count} ファイルを探索）\n"
            f"  合計: {len(entries)} 件"
        )
        return 0
    except (GenerationError, OSError) as exc:
        print(f"エラー: {exc}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
