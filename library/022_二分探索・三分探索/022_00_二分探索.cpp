#include <bits/stdc++.h>
using namespace std;

// name: 二分探索
// prefix: fnbinsearch
// description: 判定関数を外部指定する二分探索
// cpp.json from here
// 二分探索
// T bin_search<judge>(T inside, T outside, Args&&... args) : 条件を満たす側の境界値を返す
// 計算量：O(log(探索範囲の広さ)×判定1回の計算量)
// ※ insideは条件を満たし、outsideは条件を満たさず、abs(inside-outside)がオーバーフローしないこと
// ※ insideとoutsideの間では判定結果が単調であること（大小関係はどちら向きでもよい）
// ※ insideとoutside自身は判定しないため、範囲外の番兵値も指定可能
// ※ judgeは第1引数に探索位置を受け取り、boolに変換可能な値を返す関数とする
// ※ args...はそのままjudgeの第2引数以降に渡す
// ※ 実数探索に使う場合は終了幅を変更する
bool judge(long long n, long long a, long long b, long long x) {
  int d = 0;
  long long m = n;
  while (m>0) {m/=10; d++;}
  return (a*n+b*d<=x);
}
template<auto judge = judge, class T, class... Args>
T bin_search(T inside, T outside, Args&&... args) {
  while (abs(inside-outside)>1) {
    T mid = inside+(outside-inside)/2;
    if (judge(mid,args...)) {
      inside = mid;
    } else {
      outside = mid;
    }
  }
  return inside;
}
// cpp.json to here

int main () {

  // ABC146 C - Buy an Integer
  // https://atcoder.jp/contests/abc146/tasks/abc146_c
  // https://atcoder.jp/contests/abc146/submissions/80897100

  long long a, b, x;
  cin >> a >> b >> x;

  long long result = bin_search(0LL,1000000001LL,a,b,x);

  cout << result << endl;

  return 0;

}
