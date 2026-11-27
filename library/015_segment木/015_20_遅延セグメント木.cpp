#include <bits/stdc++.h>
using namespace std;

constexpr long long INF = 1001001001001001001LL;

// name: 遅延セグメント木
// prefix: fnsegmentlazy
// description: モノイドの区間作用・区間集約
// cpp.json from here
// 遅延セグメント木
// 以下で、Tは集約値の型、Fは作用の型
// コンストラクタ : LazySegmentTree(int n); : n要素をe()で初期化、O(N)
// コンストラクタ : LazySegmentTree(const vector<T>& vec); : 配列vecで初期化、O(N)
// void initialize(int n) : n要素をe()で再初期化、O(N)
// void make(const vector<T>& vec) : 配列vecを使って全要素を再構築、O(N)
// void set(int p, T x) : 位置pの値をxに変更、O(logN)
// void add(int p, T x) : 位置pの値をop(get(p),x)に変更、O(logN)
// T get(int p) : 位置pの値を返す、O(logN)
// void apply(int l, int r, F f) : [l,r)に作用fを適用、O(logN)
// T prod(int l, int r) : [l,r)の集約値を返す、O(logN)
// T all_prod() : 全区間の集約値を返す、O(1)
// ※ n>=1、make()に渡す配列の要素数はnと一致させる
// ※ initialize()とmake()は保持している遅延作用をすべてid()に戻す
// ※ op()、e()、mp()、comp()、id()は問題に応じて編集する
// ※ mp(f,x)はxに作用fを適用した結果を返す
// ※ comp(f,g)はgを先に、fを後に適用する合成作用を返す
long long op(long long a, long long b) {
  return min(a,b);
}
long long e() {
  return INF;
}
long long mp(long long f, long long x) {
  return f+x;
}
long long comp(long long f, long long g) {
  return f+g;
}
long long id() {
  return 0;
}
template<class T, T (*op)(T,T), T (*e)(), class F, T (*mapping)(F,T), F (*composition)(F,F), F (*id)()>
struct LazySegmentTree {
  int n;
  int size;
  int h;
  vector<T> values;
  vector<F> lazy;
  LazySegmentTree(int n_) {
    initialize(n_);
  }
  LazySegmentTree(const vector<T>& vec) {
    initialize(ssize(vec));
    make(vec);
  }
  void initialize(int n_) {
    assert(n_>=1);
    n = n_;
    size = 1;
    h = 0;
    while (size<n) {size <<= 1; h++;}
    values.assign(2*size,e());
    lazy.assign(size,id());
  }
  void make(const vector<T>& vec) {
    assert(ssize(vec)==n);
    for (int p=0; p<n; p++) values[p+size] = vec[p];
    for (int p=size-1; p>0; p--) values[p] = op(values[2*p],values[2*p+1]);
    lazy.assign(size,id());
  }
  void apply_at(int k, F f) {
    values[k] = mapping(f,values[k]);
    if (k<size) lazy[k] = composition(f,lazy[k]);
  }
  void push(int k) {
    apply_at(2*k,lazy[k]);
    apply_at(2*k+1,lazy[k]);
    lazy[k] = id();
  }
  void push_to(int k) {for (int i=h; i>=1; i--) push(k>>i);}
  void update(int k) {values[k] = op(values[2*k],values[2*k+1]);}
  void set(int p, T x) {
    assert(0<=p&&p<n);
    p += size;
    push_to(p);
    values[p] = x;
    while(p>1) {
      p >>= 1;
      update(p);
    }
  }
  void add(int p, T x) {
    set(p,op(get(p),x));
  }
  T all_prod() {return values[1];}
  T prod(int l, int r) {
    assert(0<=l&&l<=r&&r<=n);
    if (l == r) return e();
    l += size;
    r += size;
    push_to(l);
    push_to(r-1);
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
  T get(int p) {return prod(p,p+1);}
  void apply(int l, int r, F f) {
    assert(0<=l&&l<=r&&r<=n);
    if (l == r) return;
    l += size;
    r += size;
    push_to(l);
    push_to(r-1);
    int tmp_l = l;
    int tmp_r = r;
    while(tmp_l<tmp_r) {
      if (tmp_l&1) {apply_at(tmp_l,f); tmp_l++;}
      tmp_l >>= 1;
      if (tmp_r&1) {apply_at(tmp_r-1,f);}
      tmp_r >>= 1;
    }
    for (int i=1; i<=h; i++) {
      if ((l&((1LL<<i)-1))!=0) update(l>>i);
      if ((r&((1LL<<i)-1))!=0) update((r-1)>>i);
    }
  }
};
// cpp.json to here

int main () {

  // AALC001 B 遅延セグメント木 での使用例
  // https://atcoder.jp/contests/aalc001/tasks/aalc001_b
  // https://atcoder.jp/contests/aalc001/submissions/81106793

  int n, q;
  cin >> n >> q;

  vector<long long> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  LazySegmentTree<long long,op,e,long long,mp,comp,id> seg(a);

  for (int loop=0; loop<q; loop++) {
    
    int type;
    cin >> type;
    
    if (type==1) {

      int l, r, x;
      cin >> l >> r >> x;
      l--;
      r--;

      seg.apply(l,r+1,x);
      
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
