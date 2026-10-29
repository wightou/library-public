#include <bits/stdc++.h>
using namespace std;

constexpr long long INF = 1001001001001001001LL;

// name: Bellman-Ford法
// prefix: fnbellmanford
// description: 負辺を含むグラフの多始点最短距離・負閉路の影響判定
// cpp.json from here
// Bellman-Ford法（多始点、親記録なし）
// 以下で、graphは重み付き隣接リスト（各辺は{コスト,行先}）、startsは始点群、nは頂点数、mは辺数
// vector<long long> bellman_ford(const vector<vector<pair<T,int>>>& graph, const vector<int>& starts) : 各頂点への始点群からの最短距離を返す、O(NM+N+M)
// ※ 到達不能の距離はINF
// ※ 到達可能な負閉路の影響を受ける頂点の距離は-INF
// ※ n+1ステップでの任意経路での距離が-INF<d<INFに収まることが必要
template<class T>
vector<long long> bellman_ford(const vector<vector<pair<T,int>>>& graph, const vector<int>& starts) {
  int n = ssize(graph);
  vector<long long> distances(n,INF);
  vector<bool> in_que(n,false);
  deque<int> que;
  que.emplace_back(-1);
  for (int v : starts) {
    assert(v>=0);
    assert(v<n);
    if (in_que[v]) continue;
    in_que[v] = true;
    que.emplace_front(v);
    distances[v] = 0;
  }
  for (int d=0; ssize(que)>1; d++) {
    while (que.front()!=-1) {
      int v = que.front();
      in_que[v] = false;
      que.pop_front();
      if (d>=n||distances[v]==-INF) {
        for (auto [cost,next] : graph[v]) {
          if (distances[next]==-INF) continue;
          distances[next] = -INF;
          if (in_que[next]) continue;
          in_que[next] = true;
          que.emplace_back(next);
        }
      } else {
        for (auto [cost,next] : graph[v]) {
          if (distances[next]==-INF) continue;
          if (distances[v]+cost<distances[next]) {
            distances[next] = max(-INF,distances[v]+cost);
            if (in_que[next]) continue;
            in_que[next] = true;
            que.emplace_back(next);
          }
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

  // ABC061D Score Attack
  // https://atcoder.jp/contests/abc061/tasks/abc061_d
  // https://atcoder.jp/contests/abc061/submissions/80466359

  int n, m;
  cin >> n >> m;
  
  vector<int> u(m), v(m), w(m);
  vector<vector<pair<int,int>>> graph(n);
  for (int i=0; i<m; i++) {
    cin >> u.at(i) >> v.at(i) >> w.at(i);
    u.at(i)--;
    v.at(i)--;
    graph.at(u.at(i)).emplace_back(-w.at(i),v.at(i));
  }

  long long result = -bellman_ford(graph,{0}).at(n-1);

  if (result==INF) cout << "inf" << endl;
  else cout << result << endl;

  return 0;

}
