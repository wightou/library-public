#include <bits/stdc++.h>
using namespace std;

int main () {

  // name: getline入力
  // prefix: ingetline
  // description: getlineで1行を入力\n直前にcin >> を使っている場合は改行の読み残しに注意
  // cpp.json from here
  string s;        // snippet-replace: string ${1:s};
  getline(cin, s); // snippet-replace: getline(cin, ${1});
  // cpp.json to here

  cout << s << '\n';

  return 0;
}
