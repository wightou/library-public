#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1001001001;

// name: セグメント木
// prefix: fnsegment
// description: モノイドの一点更新・区間集約
// cpp.json from here
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
  return min(a,b);
}
template<class T>
T e() {
  return INF;
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
// cpp.json to here

int main () {

  // AALC001 A セグメント木 での使用例
  // https://atcoder.jp/contests/aalc001/tasks/aalc001_a
  // https://atcoder.jp/contests/aalc001/submissions/81106749

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  SegmentTree<int> seg(a);

  for (int loop=0; loop<q; loop++) {
    
    int type;
    cin >> type;
    
    if (type==1) {

      int i, x;
      cin >> i >> x;
      i--;

      seg.set(i,x);
      
    } else if (type==2) {

      int l, r;
      cin >> l >> r;
      l--;
      r--;

      cout << seg.prod(l,r+1) << endl;

    }

  }

  return 0;

}
