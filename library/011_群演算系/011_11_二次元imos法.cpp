#include <bits/stdc++.h>
using namespace std;

// name: 二次元imos法
// prefix: fnimos2D
// description: 二次元imos法
// cpp.json from here
// 二次元imos法
// 以下で、hとwはグリッドサイズ、uとdとlとrとcはindex
// コンストラクタ : Imos2D(int h, int w); : その行数と列数で準備、O(HW)
// void apply(int u, int l, int d, int r, T x)  : [u,d)×[l,r)にxを演算する、build()前のみ、O(1)
// void build() : 累積演算をして値を返す準備、O(HW)
// T get(int r, int c) : 位置(r,c)での値を返す、O(1)
// ※ op()の内容は任意の可換群に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
template<class T>
struct Imos2D {
  bool built = false;
  int h, w;
  vector<vector<T>> values;
  Imos2D(int h_, int w_) {
    assert(h_>=0&&w_>=0);
    h = h_; w = w_;
    values.assign(h,vector<T>(w,e()));
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
  void apply(int u, int l, int d, int r, T x) {
    assert(!built&&0<=u&&u<h&&u<=d&&d<=h&&0<=l&&l<w&&l<=r&&r<=w);
    values[u][l] = op(values[u][l],x);
    if (r<w) values[u][r] = inv(x,values[u][r]);
    if (d<h) values[d][l] = inv(x,values[d][l]);
    if (d<h&&r<w) values[d][r] = op(values[d][r],x);
  }
  void build() {
    assert(!built);
    built = true;
    for (int i=0; i<h-1; i++) for (int j=0; j<w; j++) values[i+1][j] = op(values[i][j],values[i+1][j]);
    for (int i=0; i<h; i++) for (int j=0; j<w-1; j++) values[i][j+1] = op(values[i][j],values[i][j+1]);
  }
  T get(int r, int c) {
    assert(built&&0<=r&&r<h&&0<=c&&c<w);
    return values[r][c];
  }
};
// cpp.json to here

int main () {

  // 典型90問028 Cluttered Paper での使用例（こんなものを用いなくても普通の二次元累積和で解ける）
  // https://atcoder.jp/contests/typical90/tasks/typical90_ab
  // https://atcoder.jp/contests/typical90/submissions/80220036

  int n;
  cin >> n;

  vector<int> u(n), l(n), d(n), r(n);
  for (int i=0; i<n; i++) {
    cin >> u.at(i) >> l.at(i) >> d.at(i) >> r.at(i);
  }

  int mh = 1000;
  int mw = 1000;

  // 二次元imos法構造体を準備
  Imos2D<int> im(mh,mw);

  // 範囲加算
  for (int i=0; i<n; i++) im.apply(u.at(i),l.at(i),d.at(i),r.at(i),1);

  // ビルド
  im.build();

  // カウントする
  vector<int> result(n+1,0);
  for (int i=0; i<mh; i++) {
    for (int j=0; j<mw; j++) {
      result.at(im.get(i,j))++;
    }
  }

  for (size_t i=1; i<result.size(); i++) {
    cout << result.at(i) << endl;
  }

  return 0;

}