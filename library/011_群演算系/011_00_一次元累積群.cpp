#include <bits/stdc++.h>
using namespace std;

// name: 一次元累積群
// prefix: fnaccumulation
// description: 群の累積処理による高速化
// cpp.json from here
// 一次元累積群
// 以下で、vecは元の配列、lとrはindex
// コンストラクタ : Accumulation(const vector<T>& vec); : 累積値を生成する、先頭にe()が入る「より左」型、O(N)
// T prod(int l, int r) : [l,r) の区間処理結果を返す、O(1)
// ※ op()の内容は任意の群（非可換でも可）に編集可（inv(a,b)=a^(-1)*bとe()の編集も必要）
template<class T>
struct Accumulation {
  int n;
  vector<T> values;
  Accumulation(const vector<T>& vec) {
    n = ssize(vec)+1;
    values.assign(n,e());
    for (int i=0; i<n-1; i++) values[i+1] = op(values[i],vec[i]);
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
  T prod(int l, int r) {
    assert(0<=l&&l<=r&&r<n);
    return inv(values[l],values[r]);
  }
};
// cpp.json to here

int main () {

  // 典型90問010 Score Sum Queries での使用例（こんなものを用いなくても普通の累積和で解ける）
  // https://atcoder.jp/contests/typical90/tasks/typical90_j
  // https://atcoder.jp/contests/typical90/submissions/80083250

  int n;
  cin >> n;

  vector<int> c(n), p(n);
  for (int i=0; i<n; i++) {
    cin >> c.at(i) >> p.at(i);
  }

  vector<int> p1(n,0);
  vector<int> p2(n,0);
  for (int i=0; i<n; i++) {
    if (c.at(i)==1) p1.at(i) = p.at(i);
    else p2.at(i) = p.at(i);
  }

  // 累積群のデータを、1組分と2組分を用意する
  Accumulation<int> sum1(p1);
  Accumulation<int> sum2(p2);

  int q;
  cin >> q;

  for (int loop=0; loop<q; loop++) {

    int l, r;
    cin >> l >> r;
    l--;
    r--;

    // 区間処理をして、出力
    cout << sum1.prod(l,r+1) << " " << sum2.prod(l,r+1) << endl;

  }

  return 0;

}