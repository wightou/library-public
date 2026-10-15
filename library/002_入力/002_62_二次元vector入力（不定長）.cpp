#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: 二次元vector入力（不定長）
  // prefix: inmatk
  // description: 二次元vector入力（不定長）
  // cpp.json from here
  vector<vector<int>> a(n);     // snippet-replace: vector<vector<${1|int,long long,double,string|}>> ${2:a}(${3:n});
  for (int i=0; i<n; i++) {     // snippet-replace: for (int i=0; i<${3}; i++) {
    int k;
    cin >> k;
    a.at(i).resize(k);          // snippet-replace: ${2}.at(i).resize(k);
    for (int j=0; j<k; j++) {
      cin >> a.at(i).at(j);     // snippet-replace: cin >> ${2}.at(i).at(j);
    }
  }
  // cpp.json to here

  cout << n << '\n';
  for (int i=0; i<n; i++) {
    cout << ssize(a.at(i));
    for (int x : a.at(i)) cout << ' ' << x;
    cout << '\n';
  }

  return 0;

}
