#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1000000007;

// name: 累乗mod
// prefix: fnpowermod
// description: 繰り返し二乗法による剰余付き累乗
// cpp.json from here
// 繰り返し二乗法（剰余付き累乗）
// long long power_mod(long long a, long long p) : aのp乗をmodで割った余りを返す
// 計算量 : p>=0でO(log(p+1))、p<0でO(log mod)
// ※ modは2以上2^31.5未満の値を外部で定数または変数として定義すること
// ※ p<0はmodが素数かつaがmodと互いに素な場合のみ使用可能
long long power_mod(long long a, long long p) {
  a %= mod;
  if (a<0) a += mod;
  if (p<0) {
    assert(gcd(a,mod)==1);
    p = (p%(mod-1))+mod-1;
  }
  long long result = 1;
  long long b = a;
  while (p>0) {
    if (p&1LL) result = result*b%mod;
    b = b*b%mod;
    p >>= 1;
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC178C Ubiquity での使用例
  // https://atcoder.jp/contests/abc178/tasks/abc178_c
  // https://atcoder.jp/contests/abc178/submissions/80263143

  int n;
  cin >> n;

  long long result = 0;

  result = power_mod(10,n) - 2*power_mod(9,n) + power_mod(8,n);

  result %= mod;
  if (result<0) result += mod;

  cout << result << endl;

  return 0;

}
