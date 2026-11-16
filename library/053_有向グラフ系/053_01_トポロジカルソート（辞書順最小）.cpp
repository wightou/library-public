#include <bits/stdc++.h>
using namespace std;

// name: トポロジカルソート（辞書順最小）
// prefix: fntopologicalsortmin
// description: Kahn法による辞書順最小のトポロジカルソート
// cpp.json from here
// トポロジカルソート（Kahn法・辞書順最小）
// 以下で、graphは有向グラフの隣接リスト、nは頂点数、mは辺数
// vector<int> topological_sort_min(const vector<vector<int>>& graph) : 辞書順最小のトポロジカル順に頂点を並べた配列を返す、O(N log N+M)
// ※ 有向閉路が存在する場合は空配列を返す
vector<int> topological_sort_min(const vector<vector<int>>& graph) {
  int n = ssize(graph);
  vector<int> degrees(n,0);
  priority_queue<int,vector<int>,greater<int>> que;
  vector<int> result;
  result.reserve(n);
  for (const auto& vec : graph) for (int v : vec) degrees[v]++;
  for (int i=0; i<n; i++) if (degrees[i]==0) que.emplace(i);
  while (!que.empty()) {
    int v = que.top();
    que.pop();
    result.emplace_back(v);
    for (int u : graph[v]) {
      degrees[u]--;
      if (degrees[u]==0) que.emplace(u);
    }
  }
  if (ssize(result)<n) result.clear();
  return result;
}
// cpp.json to here

int main () {

  // ABC223D Restricted Permutation での使用例
  // https://atcoder.jp/contests/abc223/tasks/abc223_d
  // https://atcoder.jp/contests/abc223/submissions/80798749

  int n, m;
  cin >> n >> m;

  vector<int> u(m), v(m);
  vector<vector<int>> graph(n);
  for (int i=0; i<m; i++) {
    cin >> u.at(i) >> v.at(i);
    u.at(i)--;
    v.at(i)--;
    graph.at(u.at(i)).emplace_back(v.at(i));
  }

  vector<int> result = topological_sort_min(graph);
  if (result.empty()) {
    cout << -1 << endl;
  } else {
    for (int i=0; i<ssize(result); i++) {
      if (i>0) cout << " ";
      cout << result[i]+1;
    }
    cout << endl;
  }

  return 0;

}
