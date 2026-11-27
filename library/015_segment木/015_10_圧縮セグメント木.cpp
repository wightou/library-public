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

// name: 圧縮セグメント木
// prefix: fnsegmentcomp
// description: 座標圧縮を用いたモノイドの一点更新・区間集約
// cpp.json from here
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
// cpp.json to here

int main () {

  // ABC231F Jealous Two での使用例
  // https://atcoder.jp/contests/abc231/tasks/abc231_f
  // https://atcoder.jp/contests/abc231/submissions/81106763

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }
  vector<int> b(n);
  for (int i=0; i<n; i++) {
    cin >> b.at(i);
  }

  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> que;
  for (int i=0; i<n; i++) {
    que.emplace(-a.at(i),b.at(i));
  }

  long long result = 0;

  // 圧縮セグメント木を用意
  CompressedSegmentTree<int,long long> seg(b);

  while (!que.empty()) {
    auto [i,j] = que.top();
    long long counter = 0;
    while (!que.empty()&&que.top()==make_pair(i,j)) {
      counter++;
      que.pop();
    }
    result += counter*seg.prod(0,j+1);
    result += counter*counter;
    seg.add(j,counter);
  }

  cout << result << endl;

  return 0;

}
