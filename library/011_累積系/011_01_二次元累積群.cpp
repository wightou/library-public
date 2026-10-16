#include <bits/stdc++.h>
using namespace std;

// name: 二次元累積群
// prefix: fnaccumulation2d
// description: 群の累積処理による高速化
// cpp.json from here
// 二次元累積群
// 以下で、vecは元の二次元配列、uとdとlとrはindex
// コンストラクタ : Accumulation2D(const vector<vector<T>>& vec); : 累積値を生成する、各行各列先頭にe()が入る、O(HW)
// T prod(int u, int l, int d, int r) : [u,d)×[l,r) の区間処理結果を返す、O(1)
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
template<class T>
struct Accumulation2D {
  int h, w;
  vector<vector<T>> values;
  Accumulation2D(const vector<vector<T>>& vec) {
    h = ssize(vec)+1;
    if (h>1) w = ssize(vec.front())+1; else w = 1;
    values.assign(h,vector<T>(w, e()));
    for (int i=0; i<h-1; i++) {
      assert(ssize(vec[i])==w-1);
      for (int j=0; j<w-1; j++) values[i+1][j+1] = op(values[i+1][j],vec[i][j]);
      for (int j=0; j<w-1; j++) values[i+1][j+1] = op(values[i+1][j+1],values[i][j+1]);
    }
  }
  T op(T a, T b) {
    return a+b;
  }
  T inv(T a, T b) {
    return b-a;
  }
  T e() {
    return 0;
  }
  T prod(int u, int l, int d, int r) {
    assert(0<=u&&u<=d&&d<h);
    assert(0<=l&&l<=r&&r<w);
    return inv(inv(values[d][r],values[d][l]),inv(values[u][r],values[u][l]));
  }
};
// cpp.json to here

int main () {

  // ABC106Dでの使用例（こんなものを用いなくても普通の二次元累積和で解ける）
  // https://atcoder.jp/contests/abc106/tasks/abc106_d
  // https://atcoder.jp/contests/abc106/submissions/80083829

  int n, m, query;
  cin >> n >> m >> query;

  vector<int> l(m), r(m);
  vector<vector<int>> vec(n,vector<int>(n,0));
  for (int i=0; i<m; i++) {
    cin >> l.at(i) >> r.at(i);
    l.at(i)--;
    r.at(i)--;
    vec.at(l.at(i)).at(r.at(i))++;
  }  

  // 二次元累積群を用意
  Accumulation2D<int> sum(vec);

  for (int loop=0; loop<query; loop++) {

    int p, q;
    cin >> p >> q;
    p--;
    q--;

    // [p,q]×[p,q]の累積を出力
    cout << sum.prod(p,p,q+1,q+1) << endl;

  }

  return 0;

}