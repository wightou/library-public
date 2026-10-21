#include <bits/stdc++.h>
using namespace std;

// 座標圧縮
// 以下で、xは圧縮前の値、yは圧縮後のindex
// コンストラクタ : Compression(const vector<T>& vec_ = {}); : ソート・重複除去して初期化、O(NlogN)
// int encode(T x) : xの圧縮後の位置を返す、O(logN)
// T decode(int y) : 位置yの圧縮前の値を返す、O(1)
// int lower(T x) : x未満の異なる座標の個数を返す、O(logN)
// int upper(T x) : x以下の異なる座標の個数を返す、O(logN)
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
  int lower(T x) {
    int y = lower_bound(vec.begin(),vec.end(),x)-vec.begin();
    return y;
  }
  int upper(T x) {
    int y = upper_bound(vec.begin(),vec.end(),x)-vec.begin();
    return y;
  }
  int encode(T x) {
    int y = lower_bound(vec.begin(),vec.end(),x)-vec.begin();
    assert(y<ssize(vec)&&vec[y] == x);
    return y;
  }
  T decode (int y) {
    assert(0<=y&&y<ssize(vec));
    return vec.at(y);
  }
  // T left (int y) {
  //   assert(1<=y&&y<ssize(vec));
  //   return vec.at(y)-vec.at(y-1);
  // }
  // T right (int y) {
  //   return left(y+1);
  // }
  int size() {
    return ssize(vec);
  }
};

// name: 圧縮Fenwick木
// prefix: fnfenwickcomp
// description: 座標圧縮を用いたFenwick木による一点更新・区間集約の高速化
// cpp.json from here
// 圧縮Fenwick木（要：座標圧縮）
// 以下で、Sは座標の型、Tは集約値の型、posは圧縮前の座標、lとrは区間端
// コンストラクタ : CompressedFenwickTree(const vector<S>& vec); : 登録する座標を指定して初期化、全要素e()、O(NlogN)
// void add(S pos, T x) : 座標posにxを演算する、O(logN)
// void set(S pos, T x) : 座標posの値をxに変更する、O(logN)
// T sum(S l, S r) : [l,r) の区間処理結果を返す、O(logN)
// T get(S pos) : 座標posの値を返す、O(logN)
// ※ add()とset()とget()は登録済みの座標のみ指定可能、sum()の区間端は未登録でも可
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
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
template<class S, class T, T(*op)(T,T) = op<T>, T(*inv)(T,T) = inv<T>, T(*e)() = e<T>>
struct CompressedFenwickTree {
  int n;
  Compression<S> comp;
  vector<T> values;
  CompressedFenwickTree(const vector<S>& vec) {
    comp = Compression(vec);
    n = comp.size();
    values.assign(n,e());
  }
  void add(S pos, T x) {
    int p = comp.encode(pos);
    assert(0<=p&&p<n);
    p++;
    while(p<=n) {
      values[p-1] = op(values[p-1],x);
      p += (p&-p);
    }
  }
  void set(S pos, T x) {
    add(pos,inv(get(pos),x));
  }
  T sum_id(int p) {
    T s = e();
    while(p>0) {
      s = op(s,values[p-1]);
      p -= (p&-p);
    }
    return s;
  }
  T sum(S pos) {return sum_id(comp.lower(pos));}
  T sum(S pos_l, S pos_r) {
    assert(pos_l <= pos_r);
    return inv(sum(pos_l),sum(pos_r));
  }
  T get(S pos) {int p = comp.encode(pos); return inv(sum_id(p),sum_id(p+1));}
};
// cpp.json to here

int main () {

  // ABC231F Jealous Two での使用例
  // https://atcoder.jp/contests/abc231/tasks/abc231_f
  // https://atcoder.jp/contests/abc231/submissions/80241836

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

  // 圧縮Fenwick木を用意
  CompressedFenwickTree<int,int> f(b); 

  while (!que.empty()) {
    auto [i,j] = que.top();
    long long counter = 0;
    while (!que.empty()&&que.top()==make_pair(i,j)) {
      counter++;
      que.pop();
    }
    result += counter*f.sum(0,j+1);
    result += counter*counter;
    f.add(j,counter);
  }

  cout << result << endl;

  return 0;

}