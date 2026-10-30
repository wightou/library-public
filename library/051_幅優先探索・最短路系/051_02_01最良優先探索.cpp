#include <bits/stdc++.h>
using namespace std;

// name: 01 BFS
// prefix: fnbfs01
// description: 重み0または1のグラフの最短距離を01BFSで求める
// cpp.json from here
// 01BFS
// 以下で、graphは隣接リスト（各辺は{コスト,行先}）、startsは始点群、nは頂点数
// vector<int> bfs01(const vector<vector<pair<int,int>>>& graph, const vector<int>& starts) : 各頂点への最短距離を返す、O(N+M)
// ※ 辺のコストは0または1であることが必要
// ※ 到達できない頂点の距離は-1
// ※ 始点群は複数指定可能（重複していてもよい）
vector<int> bfs01(const vector<vector<pair<int,int>>>& graph, const vector<int>& starts) {
  int n = ssize(graph);
  vector<int> distances(n,-1);
  deque<int> que;
  que.emplace_back(-1);
  for (int v : starts) {
    assert(v>=0);
    assert(v<n);
    que.emplace_front(v);
  }
  for (int d=0; ssize(que)>1; d++) {
    while (que.front()!=-1) {
      int v = que.front();
      que.pop_front();
      if (distances[v]!=-1) continue;
      distances[v] = d;
      for (auto [cost,next] : graph[v]) {
        assert(cost==0||cost==1);
        if (distances[next]==-1) {
          if (cost==0) que.emplace_front(next);
          else que.emplace_back(next);
        }
      }
    }
    que.pop_front();
    que.emplace_back(-1);
  }
  return distances;
}
// cpp.json to here

int main () {

  // ABC481D Autopilot での使用例
  // https://atcoder.jp/contests/abc481/tasks/abc481_d
  // https://atcoder.jp/contests/abc481/submissions/80466387

  int n, m, s, t;
  cin >> n >> m >> s >> t;
  s--;
  t--;
  
  vector<int> u(m), v(m);
  vector<vector<pair<int,int>>> graph(n);
  for (int i=0; i<m; i++) {
    cin >> u.at(i) >> v.at(i);
    u.at(i)--;
    v.at(i)--;
    graph.at(u.at(i)).emplace_back(1,v.at(i));
  }

  for (auto& vec : graph) {
    if (vec.empty()) continue;
    sort(vec.begin(),vec.end());
    vec.front().first = 0;
  }

  cout << bfs01(graph,{s}).at(t) << endl;

  return 0;
  
}
