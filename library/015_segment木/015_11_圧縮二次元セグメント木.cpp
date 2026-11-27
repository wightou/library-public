#include <bits/stdc++.h>
using namespace std;

// 座標圧縮
// 以下で、xは圧縮前の値、yは圧縮後のindex
// コンストラクタ : Compression(const vector<T>& vec_ = {}); : ソート・重複除去して初期化、O(NlogN)
// int encode(const T& x) : xの圧縮後の位置を返す、O(logN)
// T decode(int y) : 位置yの圧縮前の値を返す、O(1)
// int lower(const T& x) : x未満の異なる座標の個数を返す、O(logN)
// int upper(const T& x) : x以下の異なる座標の個数を返す、O(logN)
// T left(int y) : decode(y)-decode(y-1)を返す、Tが減算可能な場合のみ1<=y<size()で使用可、O(1)
// T right(int y) : decode(y+1)-decode(y)を返す、Tが減算可能な場合のみ0<=y<size()-1で使用可、O(1)
// int size() : 異なる座標の個数を返す、O(1)
// ※ encode(x)はxが登録済みであることが必要
// ※ left()とright()はTが減算可能な場合のみコメントアウトを解除して使用可能
template<class T>
struct Compression {
  vector<T> vec;
  Compression(const vector<T>& vec_ = {}) {
    vec = vec_;
    sort(vec.begin(),vec.end());
    vec.erase(unique(vec.begin(),vec.end()),vec.end());
  }
  int lower(const T& x) const {
    int y = lower_bound(vec.begin(),vec.end(),x)-vec.begin();
    return y;
  }
  int upper(const T& x) const {
    int y = upper_bound(vec.begin(),vec.end(),x)-vec.begin();
    return y;
  }
  int encode(const T& x) const {
    int y = lower_bound(vec.begin(),vec.end(),x)-vec.begin();
    assert(y<ssize(vec)&&vec[y] == x);
    return y;
  }
  T decode (int y) const {
    assert(0<=y&&y<ssize(vec));
    return vec.at(y);
  }
  // T left (int y) const {
  //   assert(1<=y&&y<ssize(vec));
  //   return vec.at(y)-vec.at(y-1);
  // }
  // T right (int y) const {
  //   return left(y+1);
  // }
  int size() const {
    return ssize(vec);
  }
};

// 圧縮セグメント木（要：座標圧縮）
// 以下で、Sは座標の型、Tは集約値の型、posは圧縮前の座標、lとrは区間端
// コンストラクタ : CompressedSegmentTree(const vector<S>& vec); : 更新する座標を指定し、全要素e()で初期化、O(NlogN)
// void set(const S& pos, T x) : 座標posの値をxに変更、O(logN)
// void add(const S& pos, T x) : 座標posの値をop(get(pos),x)に変更、O(logN)
// T get(const S& pos) : 座標posの値を返す（未登録ならe()）、O(logN)
// T prod(const S& l, const S& r) : [l,r)の集約値を返す、O(logN)
// T all_prod() : 全区間の集約値を返す、O(1)
// ※ set()とadd()は登録済みの座標のみ指定可能。prod()の区間端は未登録でも可
// ※ op()とe()は問題に応じて編集する（非可換モノイドにも対応）
// ※ Nは異なる登録座標の個数。登録座標が0個でも構築・集約可能
template<class T>
T op(T a, T b) {
  return a+b;
}
template<class T>
T e() {
  return 0;
}
template<class S, class T, T (*op)(T,T) = op<T>, T (*e)() = e<T>>
struct CompressedSegmentTree {
  int n;
  int size;
  Compression<S> comp;
  vector<T> values;
  CompressedSegmentTree(const vector<S>& vec) {
    comp = Compression<S>(vec);
    n = comp.size();
    size = 1;
    while (size<n) size <<= 1;
    values.assign(2*size,e());
  }
  void set(const S& pos, T x) {
    int p = comp.encode(pos);
    p += size;
    values[p] = x;
    while(p>1) {
      p >>= 1;
      values[p] = op(values[2*p],values[2*p+1]);
    }
  }
  void add(const S& pos, T x) {
    set(pos,op(get(pos),x));
  }
  T all_prod() {return values[1];}
  T prod(const S& pos_l, const S& pos_r) {
    assert(pos_l <= pos_r);
    int l = comp.lower(pos_l);
    int r = comp.lower(pos_r);
    l += size;
    r += size;
    T left = e();
    T right = e();
    while(l<r) {
      if (l&1) {left = op(left,values[l]); l++;}
      l >>= 1;
      if (r&1) {right = op(values[r-1],right);}
      r >>= 1;
    }
    return op(left,right);
  }
  T get(const S& pos) {
    int p = comp.lower(pos);
    if (p==n || !(comp.decode(p)==pos)) return e();
    return values[p+size];
  }
};

// name: 圧縮二次元セグメント木
// prefix: fnsegmentcomp2
// description: 座標圧縮を用いた可換モノイドの二次元一点更新・矩形集約
// cpp.json from here
// 圧縮二次元セグメント木（要：圧縮セグメント木・座標圧縮）
// 以下で、Sは座標の型、Tは集約値の型、(r,c)は圧縮前の座標
// コンストラクタ : CompressedSegmentTree2D(const vector<pair<S,S>>& vec); : 更新する点を登録し、全要素e()で初期化、O(Nlog²N)
// void set(const S& r, const S& c, T x) : 登録済み座標(r,c)の値をxに変更、O(log²N)
// void add(const S& r, const S& c, T x) : 登録済み座標(r,c)の値をop(get(r,c),x)に変更、O(log²N)
// T get(const S& r, const S& c) : 座標(r,c)の値を返す（未登録ならe()）、O(log²N)
// T prod(const S& u, const S& l, const S& d, const S& r) : [u,d)×[l,r)の集約値を返す、O(log²N)
// T all_prod() : 全区間の集約値を返す、O(1)
// ※ Nは登録する点の数（重複を含む）。使用メモリはO(NlogN)
// ※ set()とadd()は登録済みの点のみ指定可能。prod()の区間端は未登録でも可
// ※ 可換モノイド専用。op()とe()は問題に応じて編集する
// ※ 登録する点が0個でも構築・集約可能
// ※ S型は比較可能であることが必要。get()は整数座標を前提とし、r+1,c+1が表現範囲内であること
// template<class S,class T,...>：省略したopとeには上記の関数を利用する
template<class S, class T, T (*op)(T,T) = op<T>, T (*e)() = e<T>>
struct CompressedSegmentTree2D {
  int h;
  Compression<S> comp;
  int size;
  vector<CompressedSegmentTree<S,T,op,e>> values;
  CompressedSegmentTree2D(const vector<pair<S,S>>& vec) {
    vector<S> tmp_r;
    tmp_r.reserve(vec.size());
    for (const auto& [pos_r,pos_c] : vec) tmp_r.emplace_back(pos_r);
    comp = Compression<S>(tmp_r);
    h = comp.size();
    size = 1;
    while (size<h) size <<= 1;
    vector<vector<S>> tmp_c(2*size);
    for (const auto& [pos_r,pos_c] : vec) {
      int r = comp.encode(pos_r);
      r += size;
      while(r>0) {
        tmp_c[r].emplace_back(pos_c);
        r >>= 1;
      }
    }
    values.reserve(2*size);
    for (const auto& vec_c : tmp_c) values.emplace_back(vec_c);
  }
  void set(const S& pos_r, const S& pos_c, T x) {
    int r = comp.encode(pos_r);
    r += size;
    while(r>0) {
      if (r>=size) values[r].set(pos_c,x);
      else values[r].set(pos_c,op(values[2*r].get(pos_c),values[2*r+1].get(pos_c)));
      r >>= 1;
    }
  }
  void add(const S& pos_r, const S& pos_c, T x) {
    set(pos_r,pos_c,op(get(pos_r,pos_c),x));
  }
  T all_prod() {return values[1].all_prod();}
  T prod(const S& pos_u, const S& pos_l, const S& pos_d, const S& pos_r) {
    assert(pos_u<=pos_d&&pos_l<=pos_r);
    int u = comp.lower(pos_u);
    int d = comp.lower(pos_d);
    u += size;
    d += size;
    T s = e();
    while(u<d) {
      if (u&1) {s = op(s,values[u].prod(pos_l,pos_r)); u++;}
      u >>= 1;
      if (d&1) {s = op(s,values[d-1].prod(pos_l,pos_r));}
      d >>= 1;
    }
    return s;
  }
  T get(const S& pos_r, const S& pos_c) {
    return prod(pos_r,pos_c,pos_r+1,pos_c+1);
  }
};
// cpp.json to here

int main () {

  // ABC339G Smaller Sum での使用例
  // https://atcoder.jp/contests/abc339/tasks/abc339_g
  // https://atcoder.jp/contests/abc339/submissions/81106778

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  int q;
  cin >> q;

  // 圧縮二次元セグメント木を用意
  vector<pair<int,int>> tmp(n);
  for (int i=0; i<n; i++) tmp.at(i) = {i+1,a.at(i)};
  CompressedSegmentTree2D<int,long long> seg(tmp);
  for (int i=0; i<n; i++) seg.add(i+1,a.at(i),a.at(i));

  long long result = 0;

  for (int loop=0; loop<q; loop++) {

    long long x, y, z;
    cin >> x >> y >> z;
    x ^= result;
    y ^= result;
    z ^= result;

    result = seg.prod(x,0,y+1,z+1);

    cout << result << endl;

  }

  return 0;

}
