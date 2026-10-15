#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: vector入力 4つ
  // prefix: invec4
  // description: vector入力 4つ
  // cpp.json from here
  vector<int> a(n), b(n), c(n), d(n);                 // snippet-replace: vector<${1|int,long long,double,string|}> ${2:a}(${6:n}), ${3:b}(${6}), ${4:c}(${6}), ${5:d}(${6});
  for (int i=0; i<n; i++) {                           // snippet-replace: for (int i=0; i<${6}; i++) {
    cin >> a.at(i) >> b.at(i) >> c.at(i) >> d.at(i);  // snippet-replace: cin >> ${2}.at(i) >> ${3}.at(i) >> ${4}.at(i) >> ${5}.at(i);
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << a.at(i) << " " << b.at(i) << " " << c.at(i) << " " << d.at(i) << '\n';
  }

  return 0;
}
