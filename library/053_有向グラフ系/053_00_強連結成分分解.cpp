#include <bits/stdc++.h>
using namespace std;

// name: 強連結成分分解（Gabow法）
// prefix: fnscc
// description: 有向グラフの各頂点が属する強連結成分番号を取得
// cpp.json from here
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
// cpp.json to here

int main () {

  // 典型90問 021 Come Back in One Piece
  // https://atcoder.jp/contests/typical90/tasks/typical90_u
  // https://atcoder.jp/contests/typical90/submissions/80632986

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

  auto vec = scc(graph);

  long long result = 0;
  vector<int> counters(*max_element(vec.begin(),vec.end())+1,0);
  for (int i : vec) {
    result += counters.at(i);
    counters.at(i)++;
  }

  cout << result << endl;

  return 0;

}
