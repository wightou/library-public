// name: Codeforcesのテンプレート（マルチケース用）
// prefix: tmcfm
// description: Codeforcesなどのテンプレート（マルチケース用）\nACL非対応のところ全般用
// cpp.json from here
#include <bits/stdc++.h>
using namespace std;

/////////////////// メイン ///////////////////

int main () {

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  /////////////////// 前入力 ///////////////////

  int q;
  cin >> q;

  /////////////////// 前処理 ///////////////////



  /////////////////// ループ ///////////////////

  for (int loop=0; loop<q; loop++) {

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

  }

  /////////////////// 後処理 ///////////////////



  //////////////////// 終了 ////////////////////

  return 0;

}
// cpp.json to here