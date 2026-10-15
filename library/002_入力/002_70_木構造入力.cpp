#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // name: 木構造（隣接リスト）を入力
  // prefix: intree
  // description: 木構造（隣接リスト）を入力\n頂点番号は 0-indexed化して保管
  // cpp.json from here
  int m = n-1;                                    // snippet-replace: int ${2:m} = ${1:n}-1;
  vector<int> u(m), v(m);                         // snippet-replace: vector<int> ${3:u}(${2}), ${4:v}(${2});
  vector<vector<int>> graph(n);                   // snippet-replace: vector<vector<int>> ${5:graph}(${1});
  for (int i=0; i<m; i++) {                       // snippet-replace: for (int i=0; i<${2}; i++) {
    cin >> u.at(i) >> v.at(i);                    // snippet-replace: cin >> ${3}.at(i) >> ${4}.at(i);
    u.at(i)--;                                    // snippet-replace: ${3}.at(i)--;
    v.at(i)--;                                    // snippet-replace: ${4}.at(i)--;
    graph.at(u.at(i)).emplace_back(v.at(i));      // snippet-replace: ${5}.at(${3}.at(i)).emplace_back(${4}.at(i));
    graph.at(v.at(i)).emplace_back(u.at(i));      // snippet-replace: ${5}.at(${4}.at(i)).emplace_back(${3}.at(i));
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << i+1 << ":";
    for (int to : graph.at(i)) cout << ' ' << to+1;
    cout << '\n';
  }

  return 0;
}
