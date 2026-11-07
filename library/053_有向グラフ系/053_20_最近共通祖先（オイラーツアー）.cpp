#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1001001001;

// Sparse Table
// 以下で、aは元の配列、nは要素数、lとrは区間端
// コンストラクタ : SparseTable(const vector<T>& a); : 配列aからSparse Tableを構築する、O(N log N)
// T prod(int l, int r) : [l,r) の区間処理結果を返す、O(1)
// int size() : 要素数を返す、O(1)
// ※ op()の内容は任意の冪等なモノイド（非可換でも可）に編集可（e()の編集も必要）
// ※ 空区間のprod()はe()を返す
template<class T>
T op(T a, T b) {
  return min(a,b);
}
template<class T>
T e() {
  return {INF,-1};
}
template<class T, T(*op)(T,T) = op<T>, T(*e)() = e<T>>
struct SparseTable {
  vector<vector<T>> table;
  SparseTable(const vector<T>& a) {
    table.emplace_back(a);
    int i = 0;
    int d = 1;
    while (d*2<=size()) {
      table.emplace_back();
      for (int j=0; j+2*d<=size(); j++) table[i+1].emplace_back(op(table[i][j],table[i][j+d]));
      i++;
      d <<= 1;
    }
  }
  int size() const {return ssize(table.front());}
  T prod(int l, int r) const {
    assert(0<=l&&l<=r&&r<=size());
    if (l==r) return e();
    int i = bit_width((unsigned int)r-l)-1;
    return op(table[i][l],table[i][r-(1<<i)]);
  }
};

// name: 最近共通祖先（オイラーツアー＋RMQ）
// prefix: fnlcaeuler
// description: 通過点管理のオイラーツアーとSparse TableによるLCA
// cpp.json from here
// 最近共通祖先（オイラーツアー＋Sparse Table、非再帰）
// 以下で、graphは無向木の隣接リスト、rootは根、nは頂点数
// tuple<vector<int>,vector<int>,vector<int>> euler_tour_pass(const vector<vector<int>>& graph, int root = 0) : (in,depth,tour)を返す、O(N)
// LCAEuler(const vector<vector<int>>& graph, int root = 0) : LCAを求めるための前処理を行う、O(N log N)
// int lca(int u, int v) const : 頂点uとvの最近共通祖先を返す、O(1)
// ※ n>=1の連結な無向木を想定
// ※ in[v]はtour上での頂点vの初出位置（0-indexed）
// ※ depth[v]は根から頂点vまでの深さ（根の深さは0）
// ※ tourはDFSで通過した頂点列（長さ2N-1）
// ※ Sparse Tableには{深さ,頂点番号}の組を格納し、深さの最小値からLCAを求める
// ※ Sparse Tableのop()はmin、e()は{INF,-1}を使用する
tuple<vector<int>,vector<int>,vector<int>> euler_tour_pass(const vector<vector<int>>& graph, int root = 0) {
  int n = ssize(graph);
  assert(n>0);
  assert(root>=0&&root<n);
  vector<int> in(n,-1), tour, parents(n,-1), depth(n,-1);
  depth[root] = 0;
  tour.reserve(2*n-1);
  deque<int> que;
  que.emplace_back(root);
  while (!que.empty()) {
    int v = que.back();
    if (v==-1) {
      que.pop_back();
      if (que.back()!=root) tour.emplace_back(parents[que.back()]);
      que.pop_back();
      continue;
    }
    in[v] = ssize(tour);
    tour.emplace_back(v);
    que.emplace_back(-1);
    for (int next : graph[v]) {
      if (in[next]==-1) {
        parents[next] = v;
        depth[next] = depth[v]+1;
        que.emplace_back(next);
      }
    }
  }
  return {in,depth,tour};
}
struct LCAEuler {
  vector<int> in, depth, tour;
  SparseTable<pair<int,int>> rmq = SparseTable<pair<int,int>>({});
  LCAEuler(const vector<vector<int>>& graph, int root = 0) {
    int n = ssize(graph);
    tie(in,depth,tour) = euler_tour_pass(graph,root);
    vector<pair<int,int>> tmp(2*n-1);
    for (int i=0; i<2*n-1; i++) tmp[i] = {depth[tour[i]],tour[i]};
    rmq = SparseTable<pair<int,int>>(tmp);
  }
  int lca(int u, int v) const {
    int l = in[u];
    int r = in[v];
    if (l>r) swap(l,r);
    return rmq.prod(l,r+1).second;
  }
};
// cpp.json to here

int main () {

  // ABC014 D 閉路
  // https://atcoder.jp/contests/abc014/tasks/abc014_4
  // https://atcoder.jp/contests/abc014/submissions/80638758

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

  LCAEuler l(graph);

  int q;
  cin >> q;

  for (int loop=0; loop<q; loop++) {
    int a, b;
    cin >> a >> b;
    a--;
    b--;
    int lca = l.lca(a,b);
    cout << l.depth.at(a)+l.depth.at(b)-2*l.depth.at(lca)+1 << endl;
  }

  return 0;

}
