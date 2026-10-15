#include <bits/stdc++.h>
using namespace std;

int main () {

  vector<int> result = {3,1,4};

  // name: result（vector）を一列に出力
  // prefix: outl
  // description: vectorをスペース区切りで1行に出力
  // cpp.json from here
  for (int i=0; i<ssize(result); i++) {   // snippet-replace: for (int i=0; i<ssize(${1:result}); i++) {
    cout << result.at(i);                 // snippet-replace: cout << ${1}.at(i);
    if (i!=ssize(result)-1) cout << ' ';  // snippet-replace: if (i!=ssize(${1})-1) cout << ' ';
  }
  cout << '\n';
  // cpp.json to here

  return 0;
}
