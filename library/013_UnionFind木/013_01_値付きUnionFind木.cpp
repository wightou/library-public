#include <bits/stdc++.h>
using namespace std;

// name: 値付きUnionFind木
// prefix: fnunionfind2
// cpp.json from here
// 値付きUnionFind木
// 以下で、nは頂点数、uとvは頂点番号
// コンストラクタ : UnionFind<T>(int n); : n頂点のUnionFind木を生成する、O(N)
// int root(int u) : uが所属する成分のリーダーを返す、償却O(α(N))
// bool merge(int u, int v) : uとvを連結してtrueを返す、すでに連結済だったならfalseを返す、償却O(α(N))
// bool same(int u, int v) : uとvが連結かどうかを返す、償却O(α(N))
// int size(int u) : uが所属する成分の頂点数、償却O(α(N))
// void add(int u, T x) : 頂点番号uの値にxを加える、償却O(α(N))
// void add(int u, int v, T x) : 頂点番号[u,v)の範囲の値にxを加える、償却O((v-u)α(N))
// T get(int u) : 頂点番号uの所属する成分の値集約結果を返す、償却O(α(N))
// vector<int> leaders() : 自身がリーダーになっているもの一覧を返す、O(N)
// vector<int> affiliation() : 各要素の所属する成分番号一覧を返す、償却O(Nα(N))
// vector<vector<int>> groups() : 成分ごとに所属頂点の一覧を返す、償却O(Nα(N))
// ※ op()の内容は任意の可換モノイドに編集可（addもその演算の意味になる、e()の編集も必要）
template<class T>
struct UnionFind {
  int n;
  vector<int> parent_or_size;
  vector<T> value;
  UnionFind(int n_) {assert(n_>=0); n = n_; parent_or_size.assign(n,-1); value.assign(n,e());}
  vector<int> tmp;
  int root(int v) {
    assert(v>=0);
    assert(v<n);
    while (parent_or_size[v]>=0) {tmp.emplace_back(v); v = parent_or_size[v];}
    for (int u : tmp) parent_or_size[u] = v;
    tmp.clear();
    return v;
  }
  void op(T& a, T& b) {
    a += b;
    b = e();
  }
  T e() {
    return 0;
  }
  bool merge(int u, int v) {
    u = root(u); v = root(v);
    if (u==v) return false;
    if (parent_or_size[u]>parent_or_size[v]) swap(u,v);
    parent_or_size[u] += parent_or_size[v];
    parent_or_size[v] = u;
    op(value[u],value[v]);
    return true;
  }
  bool same(int u, int v) {return root(u) == root(v);}
  int size(int u) {return -parent_or_size[root(u)];}
  void add(int p, T x) {assert(0<=p&&p<n); op(value[root(p)],x);}
  void add(int l, int r, T x) {assert(0<=l&&l<=r&&r<=n); for (int p=l; p<r; p++) add(p,x);}
  T get(int p) {assert(0<=p&&p<n); return value[root(p)];}
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

  // ARC106Bでの使用例
  // https://atcoder.jp/contests/arc106/tasks/arc106_b
  // https://atcoder.jp/contests/arc106/submissions/80079827

  int n, m;
  cin >> n >> m;
  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }
  vector<int> b(n);
  for (int i=0; i<n; i++) {
    cin >> b.at(i);
  }
  vector<int> c(m), d(m);
  for (int i=0; i<m; i++) {
    cin >> c.at(i) >> d.at(i);
    c.at(i)--;
    d.at(i)--;
  }

  // 値付きUnionFind木をn頂点で用意
  UnionFind<long long> uf(n);

  // 各頂点、aを足してbを引く
  for (int i=0; i<n; i++) {
    uf.add(i,a.at(i)-b.at(i));
  }

  // 各辺cとdを結ぶ
  for (int j=0; j<m; j++) {
    uf.merge(c.at(j),d.at(j));
  }

  // 各リーダー、自身の値が0であるか確認
  string result = "Yes";
  for (int i : uf.leaders()) {
    if (uf.get(i)!=0) result = "No";
  }

  cout << result << '\n';

  return 0;

}