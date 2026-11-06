#include <bits/stdc++.h>
using namespace std;

// 強連結成分分解（Gabow法、非再帰）
// 以下で、graphは有向グラフの隣接リスト、nは頂点数、mは辺数
// vector<int> scc(const vector<vector<int>>& graph) : 各頂点の成分番号を返す、O(N+M)
// ※ 成分番号は0始まりの連番で、異なるSCC間の辺u→vについてid[u]<id[v]となる（トポロジカル順）
// ※ 非連結グラフ、多重辺、自己ループにも対応
vector<int> scc(const vector<vector<int>>& graph) {
  int n = ssize(graph);
  vector<int> result(n,-1);
  vector<int> order(n,-1);
  int order_id = 0;
  deque<int> que;
  for (int i=0; i<n; i++) que.emplace_back(i);
  deque<int> s, p;
  int scc_id = 0;
  while (!que.empty()) {
    int v = que.back();
    if (order[v]!=-1) {
      if (!p.empty()&&p.back()==v) {
        while (s.back()!=v) {result[s.back()] = scc_id; s.pop_back();}
        result[s.back()] = scc_id;
        s.pop_back();
        p.pop_back();
        scc_id++;
      }
      que.pop_back();
      continue;
    }
    order[v] = order_id;
    order_id++;
    s.emplace_back(v);
    p.emplace_back(v);
    for (int next : graph[v]) {
      if (order[next]!=-1) {
        if (result[next]==-1) while (order[p.back()]>order[next]) p.pop_back();
      } else {
        que.emplace_back(next);
      }
    }
  }
  for (int& i : result) i = scc_id-1-i;
  return result;
}

// name: 強連結成分縮約DAG構築
// prefix: fnsccdag
// description: 強連結成分ごとの頂点一覧と縮約DAGを構築
// cpp.json from here
// 強連結成分縮約DAG構築
// 以下で、graphは有向グラフの隣接リスト、idは各頂点のSCC成分番号、nは頂点数、mは辺数
// pair<vector<vector<int>>,vector<vector<int>>> scc_dag(const vector<vector<int>>& graph, const vector<int>& id) : 縮約DAG、成分ごとの頂点一覧を返す、O(N+M)
// ※ idは0始まりの連番を想定
// ※ dag[i]は成分iから辺が出る成分の一覧（自己ループ・多重辺なし）
// ※ groups[i]は成分iに属する元の頂点の一覧
// ※ 成分番号は変更しないため、入力idの順序をそのまま引き継ぐ
pair<vector<vector<int>>,vector<vector<int>>> scc_dag(const vector<vector<int>>& graph, const vector<int>& id) {
  int n = ssize(id);
  if (n==0) return {{},{}};
  int k = (*max_element(id.begin(),id.end()))+1;
  vector<vector<int>> dag(k);
  vector<vector<int>> groups(k);
  for (int i=0; i<n; i++) groups[id[i]].emplace_back(i);
  vector<int> stamps(k,-1);
  for (int i=0; i<k; i++) {
    stamps[i] = i;
    for (int v : groups[i]) {
      for (int next : graph[v]) {
        if (stamps[id[next]]<i) {stamps[id[next]] = i; dag[i].emplace_back(id[next]);}
      }
    }
  }
  return {dag,groups};
}
// cpp.json to here

int main () {

  // ABC245 F Endless Walk
  // https://atcoder.jp/contests/abc245/tasks/abc245_f
  // https://atcoder.jp/contests/abc245/submissions/80633012

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

  vector<int> id = scc(graph);
  auto [dag,groups] = scc_dag(graph,id);

  int result = 0;
  vector<bool> flag(ssize(dag),false);
  for (int i=ssize(dag)-1; i>=0; i--) {
    if (ssize(groups.at(i))>1) flag.at(i) = true;
    for (int v : dag.at(i)) if (flag.at(v)) flag.at(i) = true;
    if (flag.at(i)) result += ssize(groups.at(i));
  }

  cout << result << endl;

  return 0;

}
