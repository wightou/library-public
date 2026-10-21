#include <bits/stdc++.h>
using namespace std;

// Fenwick木
// 以下で、nは配列の長さ、pはindex、lとrは区間端
// コンストラクタ : FenwickTree(int n); : 長さnで初期化、全要素e()、O(N)
// void add(int p, T x) : 位置pにxを演算する、O(log N)
// void set(int p, T x) : 位置pの値をxに変更する、O(log N)
// T sum(int l, int r) : [l,r) の区間処理結果を返す、O(log N)
// T get(int p) : 位置pの値を返す、O(log N)
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
// ※ 二分探索は累積和が単調非減少の場合のみコメントアウトを解除して使用可能
template<class T>
T op(T a, T b) {
  return a+b;
}
template<class T>
T inv(T a, T b) {
  return b-a;
}
template<class T>
T e() {
  return 0;
}
template<class T, T(*op)(T,T) = op<T>, T(*inv)(T,T) = inv<T>, T(*e)() = e<T>>
struct FenwickTree {
  int n;
  vector<T> values;
  FenwickTree(int n_) {assert(n_>=1); n = n_; values.assign(n,e());}
  void add(int p, T x) {
    assert(0<=p&&p<n);
    p++;
    while(p<=n) {
      values[p-1] = op(values[p-1],x);
      p += (p&-p);
    }
  }
  void set(int p, T x) {add(p,inv(get(p),x));}
  T sum(int p) {
    assert(0<=p&&p<=n);
    T s = e();
    while(p>0) {
      s = op(s,values[p-1]);
      p -= (p&-p);
    }
    return s;
  }
  T sum(int l, int r) {
    assert(0<=l&&l<=r&&r<=n);
    return inv(sum(l),sum(r));
  }
  T get(int p) {return sum(p,p+1);}
  // int lower_bound(int l, T x) {
  //   assert(0<=l&&l<=n);
  //   if (x<=e()) return l;
  //   x = op(sum(l),x);
  //   if (x<=get(0)) return 1;
  //   int p = 1;
  //   while (p<=n&&values[p-1]<x) p <<= 1;
  //   p >>= 1;
  //   x = inv(values[p-1],x);
  //   int q = (p>>1);
  //   while (q>0) {
  //     if (p+q<=n&&values[p+q-1]<x) {p += q; x = inv(values[p-1],x);}
  //     q >>= 1;
  //   }
  //   return p+1;
  // }
};

// name: 二次元Fenwick木
// prefix: fnfenwick2
// description: 二次元Fenwick木による一点更新・矩形集約の高速化
// cpp.json from here
// 二次元Fenwick木（要：一次元Fenwick木）
// 以下で、hとwは縦横の長さ、(r,c)は位置、(u,l,d,r)は矩形の上下左右の端
// コンストラクタ : FenwickTree2D(int h, int w); : h×wで初期化、全要素e()、O(HW)
// void add(int r, int c, T x) : 位置(r,c)にxを演算する、O(logH logW)
// void set(int r, int c, T x) : 位置(r,c)の値をxに変更する、O(logH logW)
// T sum(int u, int l, int d, int r) : [u,d)×[l,r) の矩形の区間処理結果を返す、O(logH logW)
// T get(int r, int c) : 位置(r,c)の値を返す、O(logH logW)
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
template<class T, T(*op)(T,T) = op<T>, T(*inv)(T,T) = inv<T>, T(*e)() = e<T>>
struct FenwickTree2D {
  int h, w;
  vector<FenwickTree<T,op,inv,e>> values;
  FenwickTree2D(int h_, int w_) {assert(h_>=1); assert(w_>=1); h = h_; w = w_; values.assign(h,FenwickTree<T,op,inv,e>(w));}
  void add(int r, int c, T x) {
    assert(0<=r&&r<h&&0<=c&&c<w);
    r++;
    while(r<=h) {
      values[r-1].add(c,x);
      r += (r&-r);
    }
  }
  void set(int r, int c, T x) {add(r,c,inv(get(r,c),x));}
  T sum(int r, int c) {
    assert(0<=r&&r<=h&&0<=c&&c<=w);
    T s = e();
    while(r>0) {
      s = op(s,values[r-1].sum(c));
      r -= (r&-r);
    }
    return s;
  }
  T sum(int u, int l, int d, int r) {
    assert(0<=u&&u<=d&&d<=h&&0<=l&&l<=r&&r<=w);
    return inv(op(sum(u,r),sum(d,l)),op(sum(u,l),sum(d,r)));
  }
  T get(int r, int c) {return sum(r,c,r+1,c+1);}
};
// cpp.json to here

int main () {

  // ABC106 D AtCoder Express 2 での使用例（こんなものを用いなくても普通の二次元累積和で解ける）
  // https://atcoder.jp/contests/abc106/tasks/abc106_d
  // https://atcoder.jp/contests/abc106/submissions/80241821

  int n, m, q;
  cin >> n >> m >> q;

  vector<int> l(m), r(m);
  for (int i=0; i<m; i++) {
    cin >> l.at(i) >> r.at(i);
    l.at(i)--;
    r.at(i)--;
  }

  // 二次元Fenwick木を用意
  FenwickTree2D<int,op,inv,e> f(n,n);
  for (int i=0; i<m; i++) {
    f.add(l.at(i),r.at(i),1);
  }

  for (int loop=0; loop<q; loop++) {

    int p, q;
    cin >> p >> q;
    p--;
    q--;

    // データを見て出力
    cout << f.sum(p,p,q+1,q+1) << endl;

  }

}