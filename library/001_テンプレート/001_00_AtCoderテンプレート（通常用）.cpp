// name: AtCoderのテンプレート（通常用）
// prefix: tmac
// description: AtCoderのテンプレート（通常用）
// cpp.json from here
#include <bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;

// ライブラリ https://github.com/wightou/library-public

/////////////////// メイン ///////////////////

int main () {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  
  //////////////////// 入力 ////////////////////

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  //////////////// 出力変数定義 ////////////////

  int result = 0;

  //////////////////// 処理 ////////////////////

  

  //////////////////// 出力 ////////////////////

  cout << result << '\n';

  //////////////////// 終了 ////////////////////

  return 0;

}
// cpp.json to here