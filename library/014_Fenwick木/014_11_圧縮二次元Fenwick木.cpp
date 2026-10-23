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

// 圧縮Fenwick木（要：座標圧縮）
// 以下で、Sは座標の型、Tは集約値の型、posは圧縮前の座標、lとrは区間端
// コンストラクタ : CompressedFenwickTree(const vector<S>& vec); : 登録する座標を指定して初期化、全要素e()、O(NlogN)
// void add(const S& pos, const T& x) : 座標posにxを演算する、O(logN)
// void set(const S& pos, const T& x) : 座標posの値をxに変更する、O(logN)
// T sum(const S& l, const S& r) : [l,r) の区間処理結果を返す、O(logN)
// T get(const S& pos) : 座標posの値を返す、O(logN)
// ※ add()とset()とget()は登録済みの座標のみ指定可能、sum()の区間端は未登録でも可
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
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
template<class S, class T, T(*op)(const T&,const T&) = op<T>, T(*inv)(const T&,const T&) = inv<T>, T(*e)() = e<T>>
struct CompressedFenwickTree {
  int n;
  Compression<S> comp;
  vector<T> values;
  CompressedFenwickTree(const vector<S>& vec) {
    comp = Compression(vec);
    n = comp.size();
    values.assign(n,e());
  }
  void add(const S& pos, const T& x) {
    int p = comp.encode(pos);
    assert(0<=p&&p<n);
    p++;
    while(p<=n) {
      values[p-1] = op(values[p-1],x);
      p += (p&-p);
    }
  }
  void set(const S& pos, const T& x) {
    add(pos,inv(get(pos),x));
  }
  T sum_id(int p) const {
    T s = e();
    while(p>0) {
      s = op(s,values[p-1]);
      p -= (p&-p);
    }
    return s;
  }
  T sum(const S& pos) const {return sum_id(comp.lower(pos));}
  T sum(const S& pos_l, const S& pos_r) const {
    assert(pos_l <= pos_r);
    return inv(sum(pos_l),sum(pos_r));
  }
  T get(const S& pos) const {int p = comp.encode(pos); return inv(sum_id(p),sum_id(p+1));}
};

// name: 圧縮二次元Fenwick木
// prefix: fnfenwickcomp2
// description: 座標圧縮を用いた二次元Fenwick木による一点更新・矩形集約の高速化
// cpp.json from here
// 圧縮二次元Fenwick木（要：一次元圧縮Fenwick木・座標圧縮）
// 以下で、Sは座標の型、Tは集約値の型、(r,c)は圧縮前の座標、(u,l,d,r)は矩形の上下左右の端
// コンストラクタ : CompressedFenwickTree2D(const vector<pair<S,S>>& vec); : 登録する座標を指定して初期化、全要素e()、O(Nlog^2N)
// void add(const S& r, const S& c, const T& x) : 座標(r,c)にxを演算する、O(log^2N)
// void set(const S& r, const S& c, const T& x) : 座標(r,c)の値をxに変更する、O(log^2N)
// T sum(const S& u, const S& l, const S& d, const S& r) : [u,d)×[l,r) の矩形の区間処理結果を返す、O(log^2N)
// T get(const S& r, const S& c) : 座標(r,c)の値を返す、O(log^2N)
// ※ Nは登録する座標の個数、使用メモリO(NlogN)
// ※ add()とset()とget()は登録済みの座標のみ指定可能、sum()の区間端は未登録でも可
// ※ get()とset()はSが整数型の場合のみコメントアウトを解除して使用可能（座標+1がオーバーフローしないこと）
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
template<class S, class T, T(*op)(const T&,const T&) = op<T>, T(*inv)(const T&,const T&) = inv<T>, T(*e)() = e<T>>
struct CompressedFenwickTree2D {
  int h;
  Compression<S> comp;
  vector<CompressedFenwickTree<S,T,op,inv,e>> values;
  CompressedFenwickTree2D(const vector<pair<S,S>>& vec) {
    vector<S> tmp_r;
    for (const auto& [pos_r,pos_c] : vec) tmp_r.emplace_back(pos_r);
    comp = Compression(tmp_r);
    h = comp.size();
    vector<vector<S>> tmp_c(h);
    for (const auto& [pos_r,pos_c] : vec) {
      int p = comp.encode(pos_r);
      p++;
      while(p<=h) {
        tmp_c[p-1].emplace_back(pos_c);
        p += (p&-p);
      }
    }
    values.reserve(h);
    for (const auto& vec_c : tmp_c) values.emplace_back(vec_c);
  }
  void add(const S& pos_r, const S& pos_c, const T& x) {
    int r = comp.encode(pos_r);
    r++;
    while(r<=h) {
      values[r-1].add(pos_c,x);
      r += (r&-r);
    }
  }
  // void set(const S& pos_r, const S& pos_c, const T& x) {add(pos_r,pos_c,inv(get(pos_r,pos_c),x));}
  T sum(const S& pos_r, const S& pos_c) const {
    int r = comp.lower(pos_r);
    T s = e();
    while(r>0) {
      s = op(s,values[r-1].sum(pos_c));
      r -= (r&-r);
    }
    return s;
  }
  T sum(const S& pos_u, const S& pos_l, const S& pos_d, const S& pos_r) const {
    assert(pos_u <= pos_d);
    assert(pos_l <= pos_r);
    return inv(op(sum(pos_u,pos_r),sum(pos_d,pos_l)),op(sum(pos_u,pos_l),sum(pos_d,pos_r)));
  }
  // T get(const S& pos_r, const S& pos_c) const {return sum(pos_r,pos_c,pos_r+1,pos_c+1);}
};
// cpp.json to here

int main () {

  // ABC339G Smaller Sum での使用例
  // https://atcoder.jp/contests/abc339/tasks/abc339_g
  // https://atcoder.jp/contests/abc339/submissions/80242680 （const修飾子がまだついていないバージョン）

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  int q;
  cin >> q;

  // 圧縮二次元Fenwick木を用意
  vector<pair<int,int>> tmp(n);
  for (int i=0; i<n; i++) tmp.at(i) = {i+1,a.at(i)};
  CompressedFenwickTree2D<int,long long> f(tmp);
  for (int i=0; i<n; i++) f.add(i+1,a.at(i),a.at(i));

  long long result = 0;

  for (int loop=0; loop<q; loop++) {

    long long x, y, z;
    cin >> x >> y >> z;
    x ^= result;
    y ^= result;
    z ^= result;

    result = f.sum(x,0,y+1,z+1);

    cout << result << endl;

  }

  return 0;

}
