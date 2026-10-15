#include <bits/stdc++.h>
using namespace std;

int main () {

  double result = 3.25;

  // name: result（小数）を出力
  // prefix: outd
  // description: 小数点以下10桁（変更可）で出力
  // cpp.json from here
  cout << fixed << setprecision(10) << result << endl;  // snippet-replace: cout << fixed << setprecision(${1:10}) << ${2:result} << endl;
  // cpp.json to here

  return 0;
}
