#include <bits/stdc++.h>
using namespace std;

// 幅優先探索（簡易版）
// 以下で、graphは隣接リスト、startsは始点群、nは頂点数
// vector<int> bfs(const vector<vector<int>>& graph, const vector<int>& starts) : 各頂点への最短距離を返す、O(N+M)
// ※ 到達できない頂点の距離は-1
// ※ startsに同じ頂点を複数指定することはできない
vector<int> bfs(const vector<vector<int>>& graph, const vector<int>& starts) {
  int n = ssize(graph);
  vector<int> distances(n,-1);
  deque<int> que;
  for (int v : starts) {
    assert(v>=0);
    assert(v<n);
    assert(distances[v]==-1);
    distances[v] = 0;
    que.emplace_back(v);
  }
  while (!que.empty()) {
    for (int v : graph[que.front()]) {
      if (distances[v]==-1) {
        distances[v] = distances[que.front()]+1;
        que.emplace_back(v);
      }
    }
    que.pop_front();
  }
  return distances;
}

int main () {

  // 典型90問 003 Longest Circular Road
  // https://atcoder.jp/contests/typical90/tasks/typical90_c
  // https://atcoder.jp/contests/typical90/submissions/80632928

  int n;
  cin >> n;

  int m = n-1;
  vector<int> u(m), v(m);
  vector<vector<int>> graph(n);
  for (int i=0; i<m; i++) {
    cin >> u.at(i) >> v.at(i);
    u.at(i)--;
    v.at(i)--;
    graph.at(u.at(i)).emplace_back(v.at(i));
    graph.at(v.at(i)).emplace_back(u.at(i));
  }

  // name: 木の直径・中心
  // prefix: fntreediameter
  // description: 木の直径・両端点・中心・両端からの距離を取得
  // cpp.json from here
  // 木の直径・中心（要：幅優先探索簡易版）
  // graphは重みなし無向木の隣接リスト、nは頂点数（n>=1）
  // dは直径の長さ（辺数）、vertex1・vertex2は直径の両端
  // dist1・dist2は各端点からの距離配列、centersは中心頂点（1個または2個）
  // 計算量 O(N)
  int vertex0 = 0;
  vector<int> dist0 = bfs(graph,{vertex0});
  int vertex1 = max_element(dist0.begin(),dist0.end())-dist0.begin();
  vector<int> dist1 = bfs(graph,{vertex1});
  int d = *max_element(dist1.begin(),dist1.end());
  int vertex2 = max_element(dist1.begin(),dist1.end())-dist1.begin();
  vector<int> dist2 = bfs(graph,{vertex2});
  vector<int> centers;
  for (int i=0; i<n; i++) {
    if (max(dist1[i],dist2[i])==(d+1)/2) centers.emplace_back(i);
  }
  // cpp.json to here

  cout << d+1 << endl;

  return 0;

}
