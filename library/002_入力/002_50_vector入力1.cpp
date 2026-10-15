#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: vector入力 1つ
  // prefix: invec
  // description: vector入力 1つ
  // cpp.json from here
  vector<int> a(n);          // snippet-replace: vector<${1|int,long long,double,string|}> ${2:a}(${3:n});
  for (int i=0; i<n; i++) {  // snippet-replace: for (int i=0; i<${3}; i++) {
    cin >> a.at(i);          // snippet-replace: cin >> ${2}.at(i);
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << a.at(i) << '\n';
  }

  return 0;
}
