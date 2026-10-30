#include <bits/stdc++.h>
using namespace std;

// name: 幅優先探索（詳細版）
// prefix: fnbfs2
// description: 無重みグラフの幅優先探索による最短距離・親子関係・探索順序
// cpp.json from here
// 幅優先探索（詳細版）
// 以下で、graphは隣接リスト、startsは始点群、nは頂点数
// tuple<vector<int>,vector<int>,vector<vector<int>>,vector<int>> bfs(const vector<vector<int>>& graph, const vector<int>& starts) : 最短距離、親一覧、子一覧、探索順序を返す、O(N+M)
// ※ 到達できない頂点の距離と親は-1
// ※ 始点の親は-1、子一覧はBFS探索木の辺のみを含む
// ※ 探索順序は到達可能な頂点のみを含み、BFS探索木では親が子より先に現れる
// ※ startsに同じ頂点を複数回指定することはできない
tuple<vector<int>,vector<int>,vector<vector<int>>,vector<int>> bfs(const vector<vector<int>>& graph, const vector<int>& starts) {
  int n = ssize(graph);
  vector<int> distances(n,-1);
  vector<int> parents(n,-1);
  vector<vector<int>> children(n);
  vector<int> order;
  deque<int> que;
  for (int v : starts) {
    assert(v>=0);
    assert(v<n);
    assert(distances[v]==-1);
    distances[v] = 0;
    que.emplace_back(v);
    order.emplace_back(v);
  }
  while (!que.empty()) {
    for (int v : graph[que.front()]) {
      if (distances[v]==-1) {
        distances[v] = distances[que.front()]+1;
        que.emplace_back(v);
        order.emplace_back(v);
        parents[v] = que.front();
        children[que.front()].emplace_back(v);
      }
    }
    que.pop_front();
  }
  return {distances,parents,children,order};
}
// cpp.json to here

int main () {

  // ABC168D Double Dots での使用例
  // https://atcoder.jp/contests/abc168/tasks/abc168_d
  // https://atcoder.jp/contests/abc168/submissions/80466395

  int n, m;
  cin >> n >> m;

  vector<int> u(m), v(m);
  vector<vector<int>> graph(n);
  for (int i=0; i<m; i++) {
    cin >> u.at(i) >> v.at(i);
    u.at(i)--;
    v.at(i)--;
    graph.at(u.at(i)).emplace_back(v.at(i));
    graph.at(v.at(i)).emplace_back(u.at(i));
  }

  auto [distances,parents,children,order] = bfs(graph,{0});

  cout << "Yes" << endl;
  for (size_t i=1; i<parents.size(); i++) {
    cout << parents.at(i)+1 << endl;
  }

  return 0;
  
}
