#include <bits/stdc++.h>
using namespace std;

int main () {

  int n;
  cin >> n;

  // 根は0、各頂点i（1<=i<n）について親と辺の重みを順に入力
  // 無向木が標準。有向（親→子）の場合は逆向きのemplace_backを削除
  // 隣接リストは{重み,行先}の順
  // name: 重み付き根付き木（親配列・隣接リスト）を入力
  // prefix: inwrtree
  // cpp.json from here
  vector<int> parent(n,-1);                                  // snippet-replace: vector<int> ${3:parent}(${2:n},-1);
  vector<int> weight(n);                                     // snippet-replace: vector<${1|int,long long,double|}> ${4:weight}(${2});
  vector<vector<pair<int,int>>> graph(n);                    // snippet-replace: vector<vector<pair<${1},int>>> ${5:graph}(${2});
  for (int i=1; i<n; i++) {                                  // snippet-replace: for (int i=1; i<${2}; i++) {
    cin >> parent.at(i) >> weight.at(i);                     // snippet-replace: cin >> ${3}.at(i) >> ${4}.at(i);
    parent.at(i)--;                                          // snippet-replace: ${3}.at(i)--;
    graph.at(parent.at(i)).emplace_back(weight.at(i),i);     // snippet-replace: ${5}.at(${3}.at(i)).emplace_back(${4}.at(i),i);
    graph.at(i).emplace_back(weight.at(i),parent.at(i));     // snippet-replace: ${5}.at(i).emplace_back(${4}.at(i),${3}.at(i));
  }
  // cpp.json to here

  for (int i=0; i<n; i++) {
    cout << i+1 << ":";
    for (auto [weight,to] : graph.at(i)) cout << " (" << weight << "," << to+1 << ")";
    cout << "\n";
  }

  return 0;
}
