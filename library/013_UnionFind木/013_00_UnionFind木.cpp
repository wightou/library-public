#include <bits/stdc++.h>
using namespace std;

// name: UnionFind木
// prefix: fnunionfind
// description: 普通のUnionFind木
// cpp.json from here
// UnionFind木
// 以下で、nは頂点数、uとvは頂点番号
// コンストラクタ : UnionFind(int n); : n頂点のUnionFind木を生成する、O(N)
// int root(int u) : uが所属する成分のリーダーを返す、償却O(α(N))
// bool merge(int u, int v) : uとvを連結してtrueを返す、すでに連結済だったならfalseを返す、償却O(α(N))
// bool same(int u, int v) : uとvが連結かどうかを返す、償却O(α(N))
// int size(int u) : uが所属する成分の頂点数、償却O(α(N))
// vector<int> leaders() : 自身がリーダーになっているもの一覧を返す、O(N)
// vector<int> affiliation() : 各要素の所属する成分番号一覧を返す、償却O(Nα(N))
// vector<vector<int>> groups() : 成分ごとに所属頂点の一覧を返す、償却O(Nα(N))
struct UnionFind {
  int n;
  vector<int> parent_or_size;
  UnionFind(int n_) {assert(n_>=0); n = n_; parent_or_size.assign(n,-1);}
  vector<int> tmp;
  int root(int v) {
    assert(v>=0);
    assert(v<n);
    while (parent_or_size[v]>=0) {tmp.emplace_back(v); v = parent_or_size[v];}
    for (int u : tmp) parent_or_size[u] = v;
    tmp.clear();
    return v;
  }
  bool merge(int u, int v) {
    u = root(u); v = root(v);
    if (u==v) return false;
    if (parent_or_size[u]>parent_or_size[v]) swap(u,v);
    parent_or_size[u] += parent_or_size[v];
    parent_or_size[v] = u;
    return true;
  }
  bool same(int u, int v) {return root(u) == root(v);}
  int size(int u) {return -parent_or_size[root(u)];}
  vector<int> leaders() {
    vector<int> result;
    for (int i=0; i<n; i++) if (parent_or_size[i]<0) result.emplace_back(i);
    return result;
  }
  vector<int> affiliation() {
    vector<int> result(n,-1);
    vector<int> l = leaders();
    for (int i=0; i<ssize(l); i++) result[l[i]] = i;
    for (int i=0; i<n; i++) result[i] = result[root(i)];
    return result;
  }
  vector<vector<int>> groups() {
    vector<vector<int>> result;
    vector<int> aff = affiliation();
    for (int i=0; i<n; i++) {
      if (ssize(result)<=aff[i]) result.resize(aff[i]+1);
      result[aff[i]].emplace_back(i);
    }
    return result;
  }
};
// cpp.json to here

int main () {

  // ABC288Cでの使用例
  // https://atcoder.jp/contests/abc288/tasks/abc288_c
  // https://atcoder.jp/contests/abc288/submissions/80079936

  int n, m;
  cin >> n >> m;

  vector<int> a(m), b(m);
  for (int i=0; i<m; i++) {
    cin >> a.at(i) >> b.at(i);
    a.at(i)--;
    b.at(i)--;
  }

  int result = 0;

  // UnionFind木をn頂点で用意
  UnionFind uf(n);

  // 順に追加しながら、追加失敗した回数を数える
  for (int j=0; j<m; j++) {
    if (!uf.merge(a.at(j),b.at(j))) result++;
  }

  cout << result << endl;

  return 0;

}