#include <bits/stdc++.h>
using namespace std;

// name: 距離付きUnionFind木
// prefix: fnunionfind3
// cpp.json from here
// 距離付きUnionFind木
// 以下で、nは頂点数、uとvは頂点番号
// コンストラクタ : UnionFind(int n); : n頂点のUnionFind木を生成する、O(N)
// int root(int u) : uが所属する成分のリーダーを返す、償却O(α(N))
// bool merge(int u, int v, long long w) : uから見たvの距離をwとして連結してtrueを返す、すでに連結済だったならfalseを返す、償却O(α(N))
// bool same(int u, int v) : uとvが連結かどうかを返す、償却O(α(N))
// int size(int u) : uが所属する成分の頂点数、償却O(α(N))
// long long diff(int u, int v) : uから見たvの距離を返す、連結でない場合はエラー、償却O(α(N))
// vector<int> leaders() : 自身がリーダーになっているもの一覧を返す、O(N)
// vector<int> affiliation() : 各要素の所属する成分番号一覧を返す、償却O(Nα(N))
// vector<vector<int>> groups() : 成分ごとに所属頂点の一覧を返す、償却O(Nα(N))
struct UnionFind {
  int n;
  vector<int> parent_or_size;
  vector<long long> distances;
  UnionFind(int n_) {assert(n_>=0); n = n_; parent_or_size.assign(n,-1); distances.assign(n,0);}
  vector<int> tmp;
  int root(int v) {
    assert(v>=0);
    assert(v<n);
    while (parent_or_size[v]>=0) {tmp.emplace_back(v); v = parent_or_size[v];}
    reverse(tmp.begin(),tmp.end());
    for (int u : tmp) {distances[u] += distances[parent_or_size[u]]; parent_or_size[u] = v;}
    tmp.clear();
    return v;
  }
  bool merge(int u, int v, long long w) {
    if (same(u,v)) return false;
    w += distances[u]; u = root(u);
    w -= distances[v]; v = root(v);
    if (parent_or_size[u]>parent_or_size[v]) {swap(u,v); w *= -1;}
    parent_or_size[u] += parent_or_size[v];
    parent_or_size[v] = u;
    distances[v] += w;
    return true;
  }
  bool same(int u, int v) {return root(u) == root(v);}
  int size(int u) {return -parent_or_size[root(u)];}
  long long diff(int u, int v) {
    assert(same(u,v));
    return distances.at(v) - distances.at(u);
  }
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

  // ABC087/ARC090 Dでの使用例（もっと簡単にも解ける）
  // https://atcoder.jp/contests/arc090/tasks/arc090_b
  // https://atcoder.jp/contests/arc090/submissions/80080965

  int n, m;
  cin >> n >> m;

  vector<int> l(m), r(m), d(m);
  for (int i=0; i<m; i++) {
    cin >> l.at(i) >> r.at(i) >> d.at(i);
    l.at(i)--;
    r.at(i)--;
  }

  string result = "Yes";

  // 距離付きUnionFind木をn頂点で用意
  UnionFind uf(n);

  // 各辺を結ぶ、すでに結ばれていた場合は距離に矛盾がないかチェック
  for (int j=0; j<m; j++) {
    if (!uf.merge(l.at(j),r.at(j),d.at(j))) {
      if (uf.diff(l.at(j),r.at(j))!=d.at(j)) result = "No";
    }
  }

  cout << result << endl;

  return 0;

}