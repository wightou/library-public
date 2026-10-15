#include <bits/stdc++.h>
using namespace std;

int main () {

  int n = 3;

  // name: vector型result（長さn）
  // prefix: resvec
  // description: vector型のresultを定義して長さnで初期化
  // cpp.json from here
  vector<int> result(n);  // snippet-replace: vector<${1|int,long long,double,bool,string,pair<int\,int>,pair<long long\,long long>|}> ${2:result}(${3:n});
  // cpp.json to here

  cout << result.size() << '\n';

  return 0;
}
