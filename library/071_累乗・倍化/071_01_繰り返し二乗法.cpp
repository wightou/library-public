#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1000000007;

// name: 繰り返し二乗法
// prefix: fnpower
// description: 一般の繰り返し二乗法
// cpp.json from here
// 繰り返し二乗法（一般）
// T power(const T& a, long long p) : aのp乗を返す、O(log(p+1))回のop演算
// ※ pは非負であること
// ※ op()は結合法則を満たし、e()はその単位元を返すこと（交換法則は不要）
// ※ 計算途中および計算結果がTの範囲内に収まること（特に整数modのときに、int型溢れに注意）
// ※ op()がO(1)でない場合、計算量にその分の時間がかかる
template<class T>
T op(const T& a, const T& b) {
  return (a*b)%mod;
}
template<class T>
T e() {
  return 1;
}
template<class T, T(*op)(const T&,const T&) = op<T>, T(*e)() = e<T>>
T power(const T& a, long long p) {
  assert(p>=0);
  T result = e();
  T b = a;
  while (p>0) {
    if (p&1LL) result = op(result,b);
    p >>= 1;
    if (p>0) b = op(b,b);
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC178C Ubiquity での使用例
  // https://atcoder.jp/contests/abc178/tasks/abc178_c
  // https://atcoder.jp/contests/abc178/submissions/80263158

  int n;
  cin >> n;

  long long result = 0;

  result = power(10LL,n) - 2*power(9LL,n) + power(8LL,n);

  result %= mod;
  if (result<0) result += mod;

  cout << result << endl;

  return 0;

}