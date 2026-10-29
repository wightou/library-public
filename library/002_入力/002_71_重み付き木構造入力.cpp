#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: 重み付き木構造（隣接リスト）を入力
  // prefix: inwtree
  // description: 重み付き木構造（隣接リスト）を入力\n入力順は「頂点、頂点、重み」、データは「重み、行先」\n頂点番号は 0-indexed化して保管
  // cpp.json from here
  int m = n-1;                                          // snippet-replace: int ${3:m} = ${2:n}-1;
  vector<int> u(m), v(m);                               // snippet-replace: vector<int> ${4:u}(${3}), ${5:v}(${3});
  vector<int> w(m);                                     // snippet-replace: vector<${1|int,long long,double|}> ${6:w}(${3});
  vector<vector<pair<int,int>>> graph(n);               // snippet-replace: vector<vector<pair<${1},int>>> ${7:graph}(${2});
  for (int i=0; i<m; i++) {                             // snippet-replace: for (int i=0; i<${3}; i++) {
    cin >> u.at(i) >> v.at(i) >> w.at(i);               // snippet-replace: cin >> ${4}.at(i) >> ${5}.at(i) >> ${6}.at(i);
    u.at(i)--;                                          // snippet-replace: ${4}.at(i)--;
    v.at(i)--;                                          // snippet-replace: ${5}.at(i)--;
    graph.at(u.at(i)).emplace_back(w.at(i),v.at(i));    // snippet-replace: ${7}.at(${4}.at(i)).emplace_back(${6}.at(i),${5}.at(i));
    graph.at(v.at(i)).emplace_back(w.at(i),u.at(i));    // snippet-replace: ${7}.at(${5}.at(i)).emplace_back(${6}.at(i),${4}.at(i));
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << i+1 << ":";
    for (auto [weight,to] : graph.at(i)) cout << " (" << weight << ',' << to+1 << ')';
    cout << '\n';
  }

  return 0;
}
