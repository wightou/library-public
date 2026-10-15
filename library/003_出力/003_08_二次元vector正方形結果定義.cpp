#include <bits/stdc++.h>
using namespace std;

int main () {

  int n = 2;

  // name: vector型result（正方形）
  // prefix: resmatn
  // description: 二次元vector型のresultを定義してn×nで初期化
  // cpp.json from here
  vector<vector<int>> result(n,vector<int>(n));  // snippet-replace: vector<vector<${1|int,long long,double,bool,string,pair<int\,int>,pair<long long\,long long>|}>> ${2:result}(${3:n},vector<${1}>(${3}));
  // cpp.json to here

  cout << result.size() << ' ' << result.at(0).size() << '\n';

  return 0;
}
