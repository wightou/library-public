#include <bits/stdc++.h>
using namespace std;

// name: トポロジカルソート
// prefix: fntopologicalsort
// description: Kahn法による有向グラフのトポロジカルソート
// cpp.json from here
// トポロジカルソート（Kahn法）
// 以下で、graphは有向グラフの隣接リスト、nは頂点数、mは辺数
// vector<int> topological_sort(const vector<vector<int>>& graph) : トポロジカル順に頂点を並べた配列を返す、O(N+M)
// ※ 有向閉路が存在する場合は空配列を返す
// ※ トポロジカル順は一意とは限らず、辞書順最小である保証はない
vector<int> topological_sort(const vector<vector<int>>& graph) {
  int n = ssize(graph);
  vector<int> degrees(n,0);
  deque<int> que;
  vector<int> result;
  result.reserve(n);
  for (const auto& vec : graph) for (int v : vec) degrees[v]++;
  for (int i=0; i<n; i++) if (degrees[i]==0) que.emplace_back(i);
  while (!que.empty()) {
    int v = que.front();
    que.pop_front();
    result.emplace_back(v);
    for (int u : graph[v]) {
      degrees[u]--;
      if (degrees[u]==0) que.emplace_back(u);
    }
  }
  if (ssize(result)<n) result.clear();
  return result;
}
// cpp.json to here

int main () {

  // Educational DP Contest G Longest Path での使用例
  // https://atcoder.jp/contests/dp/tasks/dp_g
  // https://atcoder.jp/contests/dp/submissions/80798625

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

  vector<int> vec = topological_sort(graph);
  reverse(vec.begin(),vec.end());

  vector<int> dp(n,0);
  for (int i : vec) {
    for (int j : graph.at(i)) {
      dp.at(i) = max(dp.at(i),dp.at(j)+1);
    }
  }

  cout << *max_element(dp.begin(),dp.end()) << endl;

  return 0;

}
