#include <bits/stdc++.h>
using namespace std;

int main () {

  int h, w;
  cin >> h >> w;

  // name: 二次元vector入力（長方形）
  // prefix: inmathw
  // description: 二次元vector入力（長方形）
  // cpp.json from here
  vector<vector<int>> a(h,vector<int>(w)); // snippet-replace: vector<vector<${1|int,long long,double,string|}>> ${2:a}(${3:h},vector<${1}>(${4:w}));
  for (int i=0; i<h; i++) {                // snippet-replace: for (int i=0; i<${3}; i++) {
    for (int j=0; j<w; j++) {              // snippet-replace: for (int j=0; j<${4}; j++) {
      cin >> a.at(i).at(j);                // snippet-replace: cin >> ${2}.at(i).at(j);
    }
  }
  // cpp.json to here

  cout << h << ' ' << w << '\n';
  for (int i=0; i<h; i++) {
    for (int j=0; j<w; j++) {
      cout << a.at(i).at(j);
      if (j!=w-1) cout << ' ';
    }
    cout << '\n';
  }

  return 0;

}
