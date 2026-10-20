#include <bits/stdc++.h>
using namespace std;

// name: 一次元imos法
// prefix: fnimos
// description: 一次元imos法（和ならただの階差数列）
// cpp.json from here
// 一次元imos法（和ならただの階差数列）
// 以下で、nは配列の長さ、lとrとpはindex
// コンストラクタ : Imos(int n); : その長さで準備、O(N)
// void apply(int l, int r, T x) : 区間[l,r)にxを演算する、build()前のみ、O(1)
// void build() : 累積演算をして値を返す準備、O(N)
// T get(int p) : 位置pでの値を返す、O(1)
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
template<class T, T(*op)(T,T) = op<T>, T(*inv)(T,T) = inv<T>, T(*e)() = e<T>>
struct Imos {
  bool built = false;
  int n;
  vector<T> values;
  Imos(int n_) {
    assert(n_>=0);
    n = n_;
    values.assign(n,e());
  }
  void apply(int l, int r, T x) {
    assert(!built&&0<=l&&l<n&&l<=r&&r<=n);
    values[l] = op(values[l],x);
    if (r<n) values[r] = inv(x,values[r]);
  }
  void build() {
    assert(!built);
    built = true;
    for (int i=0; i<n-1; i++) values[i+1] = op(values[i],values[i+1]);
  }
  T get(int p) {
    assert(built&&0<=p&&p<n);
    return values[p];
  }
};
// cpp.json to here

int main () {

  // ABC014C AtColor での使用例（こんなものを用いなくても普通に解ける）
  // https://atcoder.jp/contests/abc014/tasks/abc014_3
  // https://atcoder.jp/contests/abc014/submissions/80223055

  int n;
  cin >> n;

  vector<int> a(n), b(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i) >> b.at(i);
  }

  int m = 1000001;

  // imos法構造体を準備
  Imos<int> im(m);

  // 区間加算
  for (int i=0; i<n; i++) im.apply(a.at(i),b.at(i)+1,1);

  // ビルド
  im.build();

  // 最大値を調べる
  int result = 0;
  for (int i=0; i<m; i++) result = max(result,im.get(i));

  cout << result << endl;

  return 0;

}