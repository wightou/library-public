#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: vector入力 3つ
  // prefix: invec3
  // description: vector入力 3つ
  // cpp.json from here
  vector<int> a(n), b(n), c(n);            // snippet-replace: vector<${1|int,long long,double,string|}> ${2:a}(${5:n}), ${3:b}(${5}), ${4:c}(${5});
  for (int i=0; i<n; i++) {                // snippet-replace: for (int i=0; i<${5}; i++) {
    cin >> a.at(i) >> b.at(i) >> c.at(i);  // snippet-replace: cin >> ${2}.at(i) >> ${3}.at(i) >> ${4}.at(i);
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << a.at(i) << " " << b.at(i) << " " << c.at(i) << '\n';
  }

  return 0;
}
