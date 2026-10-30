#include <bits/stdc++.h>
using namespace std;

// name: DFS木構築
// prefix: fndfs
// description: 無向グラフのDFS木の親・深さ・行きがけ順を取得
// cpp.json from here
// DFS木構築（非再帰、単一始点）
// 以下で、graphは無向グラフの隣接リスト、startは始点、nは頂点数、mは辺数
// tuple<vector<int>,vector<int>,vector<int>> dfs(const vector<vector<int>>& graph, int start) : 親一覧、深さ一覧、行きがけ順を返す、O(N+M)
// ※ 始点の親は-1、深さは0
// ※ 到達不能な頂点の親と深さは-1
// ※ orderには到達可能な頂点のみを行きがけ順に格納し、親は子より先に現れる
// ※ 訪問した連結成分内では、DFS木に採用されなかった辺の両端は祖先と子孫の関係になる
// ※ スタック投入時に親を仮記録し、取り出し時に訪問を確定する
tuple<vector<int>,vector<int>,vector<int>> dfs(const vector<vector<int>>& graph, int start) {
  int n = ssize(graph);
  vector<int> parents(n,-1);
  vector<int> depths(n,-1);
  vector<int> order;
  deque<int> que;
  assert(start>=0);
  assert(start<n);
  que.emplace_back(start);
  while (!que.empty()) {
    int v = que.back();
    que.pop_back();
    if (depths[v]!=-1) continue;
    order.emplace_back(v);
    if (parents[v]!=-1) depths[v] = depths[parents[v]]+1;
    else depths[v] = 0;
    for (int next : graph[v]) {
      if (depths[next]==-1) {
        que.emplace_back(next);
        parents[next] = v;
      }
    }
  }
  return {parents,depths,order};
}
// cpp.json to here

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

int main () {

  // ABC251F Two Spanning Trees での使用例
  // https://atcoder.jp/contests/abc251/tasks/abc251_f
  // https://atcoder.jp/contests/abc251/submissions/80480927

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

  auto [parents_dfs,depths_dfs,order_dfs] = dfs(graph,0);
  auto [distances_bfs,parents_bfs,children_bfs,order_bfs] = bfs(graph,{0});

  for (int i=1; i<n; i++) {
    cout << i+1 << " " << parents_dfs.at(i)+1 << endl;
  }
  for (int i=1; i<n; i++) {
    cout << i+1 << " " << parents_bfs.at(i)+1 << endl;
  }

  return 0;

}
