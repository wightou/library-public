#include <bits/stdc++.h>
using namespace std;

// name: 自作Fenwick木
// prefix: fnfenwick
// description: Fenwick木による一点更新・区間集約の高速化
// cpp.json from here
// Fenwick木
// 以下で、nは配列の長さ、pはindex、lとrは区間端
// コンストラクタ : FenwickTree(int n); : 長さnで初期化、全要素e()、O(N)
// void add(int p, const T& x) : 位置pにxを演算する、O(log N)
// void set(int p, const T& x) : 位置pの値をxに変更する、O(log N)
// T sum(int l, int r) : [l,r) の区間処理結果を返す、O(log N)
// T get(int p) : 位置pの値を返す、O(log N)
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
// ※ 二分探索は累積和が単調非減少の場合のみコメントアウトを解除して使用可能
template<class T>
T op(const T& a, const T& b) {
  return a+b;
}
template<class T>
T inv(const T& a, const T& b) {
  return b-a;
}
template<class T>
T e() {
  return 0;
}
template<class T, T(*op)(const T&,const T&) = op<T>, T(*inv)(const T&,const T&) = inv<T>, T(*e)() = e<T>>
struct FenwickTree {
  int n;
  vector<T> values;
  FenwickTree(int n_) {assert(n_>=1); n = n_; values.assign(n,e());}
  void add(int p, const T& x) {
    assert(0<=p&&p<n);
    p++;
    while(p<=n) {
      values[p-1] = op(values[p-1],x);
      p += (p&-p);
    }
  }
  void set(int p, const T& x) {add(p,inv(get(p),x));}
  T sum(int p) const {
    assert(0<=p&&p<=n);
    T s = e();
    while(p>0) {
      s = op(s,values[p-1]);
      p -= (p&-p);
    }
    return s;
  }
  T sum(int l, int r) const {
    assert(0<=l&&l<=r&&r<=n);
    return inv(sum(l),sum(r));
  }
  T get(int p) const {return sum(p,p+1);}
  // int lower_bound(int l, T x) const {
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
// cpp.json to here

int main () {

  // Library Practice B Fenwick Tree での使用例
  // https://atcoder.jp/contests/practice2/tasks/practice2_b
  // https://atcoder.jp/contests/practice2/submissions/80223789 （const修飾子がまだついていないバージョン）

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  FenwickTree<long long> f(n);
  for (int i=0; i<n; i++) f.add(i,a.at(i));

  for (int loop=0; loop<q; loop++) {
    
    int type;
    cin >> type;
    
    if (type==0) {

      int p, x;
      cin >> p >> x;
      f.add(p,x);

    } else if (type==1) {

      int l, r;
      cin >> l >> r;
      cout << f.sum(l,r) << endl;

    }

  }


  return 0;

}
