#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: 二次元vector入力（正方形）
  // prefix: inmatn
  // description: 二次元vector入力（正方形）
  // cpp.json from here
  vector<vector<int>> a(n,vector<int>(n)); // snippet-replace: vector<vector<${1|int,long long,double,string|}>> ${2:a}(${3:n},vector<${1}>(${3}));
  for (int i=0; i<n; i++) {                // snippet-replace: for (int i=0; i<${3}; i++) {
    for (int j=0; j<n; j++) {              // snippet-replace: for (int j=0; j<${3}; j++) {
      cin >> a.at(i).at(j);                // snippet-replace: cin >> ${2}.at(i).at(j);
    }
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    for (int j=0; j<n; j++) {
      cout << a.at(i).at(j);
      if (j!=n-1) cout << ' ';
    }
    cout << '\n';
  }

  return 0;

}
