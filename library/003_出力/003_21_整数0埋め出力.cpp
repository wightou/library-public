#include <bits/stdc++.h>
using namespace std;

int main () {

  int result = 42;

  // name: result（整数）を右揃えで出力
  // prefix: outi
  // description: 埋め文字と最小表示幅を指定（初期値は0埋め4文字）\nsetfillの設定は以後の出力にも残る
  // cpp.json from here
  cout << setfill('0') << right << setw(4) << result << endl;  // snippet-replace: cout << setfill('${1:0}') << right << setw(${2:4}) << ${3:result} << endl;
  // cpp.json to here

  return 0;
}
