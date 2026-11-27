#include <bits/stdc++.h>
using namespace std;

// セグメント木
// コンストラクタ : SegmentTree(int n); : n要素をe()で初期化、O(N)
// コンストラクタ : SegmentTree(const vector<T>& vec); : 配列vecで初期化、O(N)
// void initialize(int n) : n要素をe()で再初期化、O(N)
// void make(const vector<T>& vec) : 配列vecを使って全要素を再構築、O(N)
// void set(int p, T x) : 位置pの値をxに変更、O(logN)
// void add(int p, T x) : 位置pの値をop(get(p),x)に変更、O(logN)
// T get(int p) : 位置pの値を返す、O(1)
// T prod(int l, int r) : [l,r)の集約値を返す、O(logN)
// T all_prod() : 全区間の集約値を返す、O(1)
// ※ n>=1、make()に渡す配列の要素数はnと一致させる
// ※ op()とe()は問題に応じて編集する（非可換モノイドにも対応）
template<class T>
T op(T a, T b) {
  return a+b;
}
template<class T>
T e() {
  return 0;
}
template<class T, T (*op)(T,T) = op<T>, T (*e)() = e<T>>
struct SegmentTree {
  int n;
  int size;
  vector<T> values;
  SegmentTree(int n_) {
    initialize(n_);
  }
  SegmentTree(const vector<T>& vec) {
    initialize(ssize(vec));
    make(vec);
  }
  void initialize(int n_) {
    assert(n_>=1);
    n = n_;
    size = 1;
    while (size<n) size <<= 1;
    values.assign(2*size,e());
  }
  void make(const vector<T>& vec) {
    assert(ssize(vec)==n);
    for (int p=0; p<n; p++) values[p+size] = vec[p];
    for (int p=size-1; p>0; p--) values[p] = op(values[2*p],values[2*p+1]);
  }
  void set(int p, T x) {
    assert(0<=p&&p<n);
    p += size;
    values[p] = x;
    while(p>1) {
      p >>= 1;
      values[p] = op(values[2*p],values[2*p+1]);
    }
  }
  void add(int p, T x) {
    set(p,op(get(p),x));
  }
  T all_prod() {return values[1];}
  T prod(int l, int r) {
    assert(0<=l&&l<=r&&r<=n);
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
  T get(int p) {assert(0<=p&&p<n); return values[p+size];}
};

// name: 二次元セグメント木
// prefix: fnsegment2
// description: 可換モノイドの二次元一点更新・矩形集約
// cpp.json from here
// 二次元セグメント木（要：セグメント木）
// コンストラクタ : SegmentTree2D(int h, int w); : h×w要素をe()で初期化、O(HW)
// コンストラクタ : SegmentTree2D(const vector<vector<T>>& mat); : 二次元配列matで初期化、O(HW)
// void initialize(int h, int w) : h×w要素をe()で再初期化、O(HW)
// void make(const vector<vector<T>>& mat) : 二次元配列matを使って全要素を再構築、O(HW)
// void set(int r, int c, T x) : 座標(r,c)の値をxに変更、O(logH logW)
// void add(int r, int c, T x) : 座標(r,c)の値をop(get(r,c),x)に変更、O(logH logW)
// T get(int r, int c) : 座標(r,c)の値を返す、O(1)
// T prod(int u, int l, int d, int r) : [u,d)×[l,r)の集約値を返す、O(logH logW)
// T all_prod() : 全区間の集約値を返す、O(1)
// ※ h,w>=1、matはh×wの矩形配列とする（空配列は非対応）
// ※ 可換モノイド専用。op()とe()は問題に応じて編集する
template<class T, T (*op)(T,T) = op<T>, T (*e)() = e<T>>
struct SegmentTree2D {
  int h, w;
  int size_h;
  vector<SegmentTree<T,op,e>> values;
  SegmentTree2D(int h_, int w_) {
    initialize(h_,w_);
  }
  SegmentTree2D(const vector<vector<T>>& mat) {
    initialize(ssize(mat),ssize(mat[0]));
    make(mat);
  }
  void initialize (int h_, int w_) {
    assert(h_>=1&&w_>=1);
    h = h_;
    size_h = 1;
    while (size_h<h) size_h <<= 1;
    w = w_;
    values.assign(2*size_h,SegmentTree<T,op,e>(w));
  }
  void make(const vector<vector<T>>& mat) {
    assert(ssize(mat)==h);
    for (int r=0; r<h; r++) {
      assert(ssize(mat[r])==w);
      values[r+size_h].make(mat[r]);
    }
    vector<T> tmp(w,e());
    for (int r=size_h-1; r>0; r--) {
      for (int c=0; c<w; c++) tmp[c] = op(values[2*r].get(c),values[2*r+1].get(c));
      values[r].make(tmp);
    } 
  }
  void set(int r, int c, T x) {
    assert(0<=r&&r<h&&0<=c&&c<w);
    r += size_h;
    while(r>0) {
      if (r>=size_h) values[r].set(c,x);
      else values[r].set(c,op(values[2*r].get(c),values[2*r+1].get(c)));
      r >>= 1;
    }
  }
  void add(int r, int c, T x) {
    set(r,c,op(get(r,c),x));
  }
  T all_prod() {return values[1].all_prod();}
  T prod(int u, int l, int d, int r) {
    assert(0<=u&&u<=d&&d<=h&&0<=l&&l<=r&&r<=w);
    u += size_h;
    d += size_h;
    T s = e();
    while(u<d) {
      if (u&1) {s = op(s,values[u].prod(l,r)); u++;}
      u >>= 1;
      if (d&1) {s = op(s,values[d-1].prod(l,r));}
      d >>= 1;
    }
    return s;
  }
  T get(int r, int c) {assert(0<=r&&r<h&&0<=c&&c<w); return values[r+size_h].get(c);}
};
// cpp.json to here

int main () {

  // ABC106D AtCoder Express 2 での使用例（二次元累積和でも解ける）
  // https://atcoder.jp/contests/abc106/tasks/abc106_d
  // https://atcoder.jp/contests/abc106/submissions/81106756

  int n, m, q;
  cin >> n >> m >> q;

  vector<int> l(m), r(m);
  for (int i=0; i<m; i++) {
    cin >> l.at(i) >> r.at(i);
    l.at(i)--;
    r.at(i)--;
  }

  vector<vector<int>> mat(n,vector<int>(n));
  for (int i=0; i<m; i++) {
    mat.at(l.at(i)).at(r.at(i))++;
  }

  // 二次元セグメント木を配列から初期化
  SegmentTree2D<int> seg(mat);

  for (int loop=0; loop<q; loop++) {

    int p, q;
    cin >> p >> q;
    p--;
    q--;

    // 区間[p,q]内に収まる列車の本数を出力
    cout << seg.prod(p,p,q+1,q+1) << endl;

  }

  return 0;

}
