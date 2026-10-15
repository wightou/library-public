#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: vector入力 2つ
  // prefix: invec2
  // description: vector入力 2つ
  // cpp.json from here
  vector<int> a(n), b(n);       // snippet-replace: vector<${1|int,long long,double,string|}> ${2:a}(${4:n}), ${3:b}(${4});
  for (int i=0; i<n; i++) {     // snippet-replace: for (int i=0; i<${4}; i++) {
    cin >> a.at(i) >> b.at(i);  // snippet-replace: cin >> ${2}.at(i) >> ${3}.at(i);
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << a.at(i) << " " << b.at(i) << '\n';
  }

  return 0;
}
