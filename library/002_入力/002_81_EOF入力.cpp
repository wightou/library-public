#include <bits/stdc++.h>
using namespace std;

int main () {

  // name: EOF入力
  // prefix: ineof
  // description: EOFまで入力しvectorに格納\n入力が終了するか、読み取りに失敗するとループを抜ける
  // cpp.json from here
  int num;                     // snippet-replace: ${1|int,long long,double,string|} ${2:num};
  vector<int> a;               // snippet-replace: vector<${1}> ${3:a};
  while (cin >> num) {         // snippet-replace: while (cin >> ${2}) {
    a.emplace_back(num);       // snippet-replace: ${3}.emplace_back(${2});
  }
  // cpp.json to here

  for (int x : a) {
    cout << x << '\n';
  }

  return 0;
}
