#include <bits/stdc++.h>
using namespace std;

int main () {

  int h = 2, w = 3;

  // name: vector型result（長方形）
  // prefix: resmathw
  // description: 二次元vector型のresultを定義してh×wで初期化
  // cpp.json from here
  vector<vector<int>> result(h,vector<int>(w));  // snippet-replace: vector<vector<${1|int,long long,double,bool,string,pair<int\,int>,pair<long long\,long long>|}>> ${2:result}(${3:h},vector<${1}>(${4:w}));
  // cpp.json to here

  cout << result.size() << ' ' << result.at(0).size() << '\n';

  return 0;
}
