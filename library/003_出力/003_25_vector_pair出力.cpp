#include <bits/stdc++.h>
using namespace std;

int main () {

  vector<pair<int,int>> result = {{2,5},{4,7}};

  // name: result（vector<pair>）を縦に出力
  // prefix: outpair
  // description: vector<pair>をfirst secondの順で1組ずつ改行して出力
  // cpp.json from here
  for (auto [i, j] : result) {  // snippet-replace: for (auto [i, j] : ${1:result}) {
    cout << i << ' ' << j << '\n';
  }
  // cpp.json to here

  return 0;
}
