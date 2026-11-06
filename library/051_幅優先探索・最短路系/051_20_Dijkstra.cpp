#include <bits/stdc++.h>
using namespace std;

// name: Dijkstra法
// prefix: fndijkstra
// description: 非負重みグラフの多始点最短距離（親記録なし）
// cpp.json from here
// Dijkstra法（親記録なし、多始点）
// 以下で、graphは重み付き隣接リスト（各辺は{コスト,行先}）、startsは始点群、nは頂点数、mは辺数、sは始点数
// vector<long long> dijkstra(const vector<vector<pair<T,int>>>& graph, const vector<int>& starts) : 各頂点への始点群からの最短距離を返す、O(N+(M+S)log(M+S+1))
// ※ 辺のコストは非負であることが必要
// ※ 到達できない頂点の距離は-1
template<class T>
vector<long long> dijkstra(const vector<vector<pair<T,int>>>& graph, const vector<int>& starts) {
  int n = ssize(graph);
  vector<long long> distances(n,-1);
  priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> que;
  for (int v : starts) {
    assert(v>=0);
    assert(v<n);
    que.emplace(0,v);
  }
  while (!que.empty()) {
    auto [dist,vertex] = que.top();
    que.pop();
    if (distances[vertex]!=-1) continue;
    distances[vertex] = dist;
    for (pair<long long,int> next : graph[vertex]) {
      if (distances[next.second]==-1) {next.first += dist; que.emplace(next);}
    }
  }
  return distances;
}
// cpp.json to here

int main () {

  // ABC340D Super Takahashi Bros. での使用例
  // https://atcoder.jp/contests/abc340/tasks/abc340_d
  // https://atcoder.jp/contests/abc340/submissions/80466368

  int n;
  cin >> n;

  vector<int> a(n-1), b(n-1), x(n-1);
  vector<vector<pair<int,int>>> graph(n);
  for (int i=0; i<n-1; i++) {
    cin >> a.at(i) >> b.at(i) >> x.at(i);
    x.at(i)--;
    graph.at(i).emplace_back(a.at(i),i+1);
    graph.at(i).emplace_back(b.at(i),x.at(i));
  }

  cout << dijkstra(graph,{0}).at(n-1) << endl;

  return 0;
  
}
