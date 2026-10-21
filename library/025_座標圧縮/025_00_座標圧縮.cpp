#include <bits/stdc++.h>
using namespace std;

// name: 座標圧縮
// prefix: fncompression
// description: 座標圧縮による値の変換・復元
// cpp.json from here
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
// cpp.json to here

int main () {
  
  // ABC036C - 座圧 での使用例
  // https://atcoder.jp/contests/abc036/tasks/abc036_c
  // https://atcoder.jp/contests/abc036/submissions/80241800

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  // 座標圧縮を用意
  Compression<int> comp(a);

  // 圧縮して出力
  for (int i=0; i<n; i++) cout << comp.encode(a.at(i)) << endl;

  return 0;

}