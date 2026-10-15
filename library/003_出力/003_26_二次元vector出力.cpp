#include <bits/stdc++.h>
using namespace std;

int main () {

  vector<vector<int>> result = {{1,2,3},{4},{}};

  // name: result（二次元vector）を出力
  // prefix: outmat
  // description: 各行をスペース区切りで出力（不定長の行にも対応）
  // cpp.json from here
  for (int i=0; i<ssize(result); i++) {           // snippet-replace: for (int i=0; i<ssize(${1:result}); i++) {
    for (int j=0; j<ssize(result.at(i)); j++) {   // snippet-replace: for (int j=0; j<ssize(${1}.at(i)); j++) {
      cout << result.at(i).at(j);                 // snippet-replace: cout << ${1}.at(i).at(j);
      if (j!=ssize(result.at(i))-1) cout << ' ';  // snippet-replace: if (j!=ssize(${1}.at(i))-1) cout << ' '; 
    }
    cout << '\n';
  }
  // cpp.json to here

  return 0;
}
