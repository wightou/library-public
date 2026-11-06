#include <bits/stdc++.h>
using namespace std;

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

// name: 橋検出（要：DFS木構築）
// prefix: fnbridges
// description: 無向グラフの橋を列挙
// cpp.json from here
// 橋検出（連結無向グラフ）
// 以下で、graphは無向グラフの隣接リスト、nは頂点数、mは辺数
// vector<pair<int,int>> find_bridges(const vector<vector<int>>& graph) : 橋の両端（0-indexed）を列挙する、O(N+M)
// ※ 多重辺がある場合も、各辺を別々の辺として扱う
vector<pair<int,int>> find_bridges(const vector<vector<int>>& graph) {
  if (graph.empty()) return {};
  int n = ssize(graph);
  vector<pair<int,int>> result;
  auto [parents,depths,order] = dfs(graph,0);
  assert(ssize(order)==n);
  vector<int> counters(n,0);
  for (int i=0; i<n; i++) {
    for (int j : graph[i]) {
      if (depths[i]>depths[j]) {counters[i]++; counters[j]--;}
    }
  }
  reverse(order.begin(),order.end());
  for (int i : order) {
    if (parents[i]==-1) continue;
    if (counters[i]==1) result.emplace_back(i,parents[i]);
    counters[parents[i]] += counters[i];
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC075C Bridge での使用例
  // https://atcoder.jp/contests/abc075/tasks/abc075_c
  // https://atcoder.jp/contests/abc075/submissions/80632951
  // （もっと単純に全部探索して解ける）

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

  vector<pair<int,int>> bridges = find_bridges(graph);

  cout << ssize(bridges) << endl;

  return 0;

}
