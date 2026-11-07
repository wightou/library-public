#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // 根は0、各頂点i（1<=i<n）の親が1-indexedで順に与えられる
  // 無向木が標準。有向（親→子）の場合は逆向きのemplace_backを削除
  // name: 根付き木（親配列・隣接リスト）を入力
  // prefix: inrtree
  // cpp.json from here
  vector<int> parent(n,-1);                                  // snippet-replace: vector<int> ${2:parent}(${1:n},-1);
  vector<vector<int>> graph(n);                              // snippet-replace: vector<vector<int>> ${3:graph}(${1});
  for (int i=1; i<n; i++) {                                  // snippet-replace: for (int i=1; i<${1}; i++) {
    cin >> parent.at(i);                                     // snippet-replace: cin >> ${2}.at(i);
    parent.at(i)--;                                          // snippet-replace: ${2}.at(i)--;
    graph.at(parent.at(i)).emplace_back(i);                  // snippet-replace: ${3}.at(${2}.at(i)).emplace_back(i);
    graph.at(i).emplace_back(parent.at(i));                  // snippet-replace: ${3}.at(i).emplace_back(${2}.at(i));
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << i+1 << ":";
    for (int to : graph.at(i)) cout << " " << to+1;
    cout << "\n";
  }

  return 0;
}
