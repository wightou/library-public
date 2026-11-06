#include <bits/stdc++.h>
using namespace std;

// name: オイラーツアー（頂点の出入り）
// prefix: fneulertour
// description: 木の頂点の入場・退場位置と長さ2Nの出入り順を取得
// cpp.json from here
// オイラーツアー（頂点の出入り、非再帰）
// 以下で、graphは無向木の隣接リスト、rootは根、nは頂点数
// tuple<vector<int>,vector<int>,vector<int>> euler_tour_io(const vector<vector<int>>& graph, int root = 0) : 入場位置、退場位置、出入り順を返す、O(N)
// ※ n>=1の連結な無向木を想定
// ※ in[v]とout[v]は頂点vの入場・退場位置（0-indexed）
// ※ tourは長さ2Nで、各頂点は入場時と退場時に1回ずつ登場する
// ※ tour[in[v]]==tour[out[v]]==v
// ※ 頂点vの部分木の出入りは区間[in[v],out[v]]に含まれる
// ※ 入場位置に値、退場位置に単位元を配置すれば、部分木のモノイド集約に利用できる
// ※ 入場位置に値、退場位置に逆元を配置すれば、根からの経路の群演算に利用できる
tuple<vector<int>,vector<int>,vector<int>> euler_tour_io(const vector<vector<int>>& graph, int root = 0) {
  int n = ssize(graph);
  assert(n>0);
  assert(root>=0&&root<n);
  vector<int> in(n,-1), out(n,-1), tour;
  tour.reserve(2*n);
  deque<int> que;
  que.emplace_back(root);
  while (!que.empty()) {
    int v = que.back();
    if (v==-1) {
      que.pop_back();
      out[que.back()] = ssize(tour);
      tour.emplace_back(que.back());
      que.pop_back();
      continue;
    }
    in[v] = ssize(tour);
    tour.emplace_back(v);
    que.emplace_back(-1);
    for (int next : graph[v]) {
      if (in[next]==-1) que.emplace_back(next);
    }
  }
  return {in,out,tour};
}
// cpp.json to here

int main () {

  // ABC187E Through Path
  // https://atcoder.jp/contests/abc187/tasks/abc187_e
  // https://atcoder.jp/contests/abc187/submissions/80634651

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

  int q;
  cin >> q;

  vector<int> t(q), e(q), x(q);
  for (int i=0; i<q; i++) {
    cin >> t.at(i) >> e.at(i) >> x.at(i);
    e.at(i)--;
  }

  auto [in,out,tour] = euler_tour_io(graph);

  vector<long long> vec(2*n,0);
  for (int i=0; i<q; i++) {
    int l = u.at(e.at(i));
    int r = v.at(e.at(i));
    if (t.at(i)==1) swap(l,r);
    if (in.at(l)>in.at(r)) {
      swap(l,r);
      vec.at(0) += x.at(i);
      x.at(i)*=-1;
    }
    vec.at(in.at(r)) += x.at(i);
    vec.at(out.at(r)) -= x.at(i);
  }

  vector<long long> sum(2*n,0);
  partial_sum(vec.begin(),vec.end(),sum.begin());

  for (int i=0; i<n; i++) {
    cout << sum.at(in.at(i)) << endl;
  }

  return 0;

}
