#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1000000007;

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

// 階乗と逆階乗のmod計算（要：累乗mod）
// void make_factorial(int n) : nまでの階乗と逆階乗を前計算、不足分のみ追加、O(n) ※ log mod は定数扱いで
// long long factorial(int n) : n! modを返す、延べO(n_max) ※ log mod は定数扱いで
// long long fact_inv(int n) : n!の逆元modを返す、延べO(n_max) ※ log mod は定数扱いで
// ※ modは素数であること
// ※ factorial_data[i]はi! mod、fact_inv_data[i]はその逆元
// ※ factorial()とfact_inv()は0<=n<modで使用すること
// ※ 未計算の場合は要求値の2倍（上限mod-1）まで階乗・逆階乗をまとめて計算する
// ※ 計算済みの範囲は再計算せず、データを保持する
// ※ make_factorial()を直接呼ぶ場合は0<=n<modであること
vector<long long> factorial_data(1,1);
vector<long long> fact_inv_data(1,1);
void make_factorial(int n) {
  assert(n>=0);
  assert(n<mod);
  int m = ssize(factorial_data);
  if (m>n) return;
  factorial_data.resize(n+1,1);
  for (int i=m; i<=n; i++) {
    factorial_data[i] = factorial_data[i-1]*i%mod;
  }
  fact_inv_data.resize(n+1,1);
  fact_inv_data[n] = power_mod(factorial_data[n],-1);
  for (int i=n; i>=m; i--) {
    fact_inv_data[i-1] = fact_inv_data[i]*i%mod;
  }
}
long long factorial(int n) {
  assert(n>=0);
  assert(n<mod);
  if (ssize(factorial_data)<=n) make_factorial(min(2LL*n,(long long)mod-1));
  return factorial_data[n];
}
long long fact_inv(int n) {
  assert(n>=0);
  assert(n<mod);
  if (ssize(factorial_data)<=n) make_factorial(min(2LL*n,(long long)mod-1));
  return fact_inv_data[n];
}

// 二項係数とその逆数（要：階乗mod）
// long long comb(int n, int r) : nCr mod modを返す、計算済みならO(1)
// long long comb_inv(int n, int r) : nCrの逆元を返す、計算済みならO(1)
// ※ modは素数、0<=n<modの範囲で使用すること
// ※ 階乗・逆階乗は不足時に自動拡張する
// ※ comb()はr<0またはr>nで0、comb_inv()は0<=r<=nが必要
long long comb(int n, int r) {
  if (r<0) return 0;
  if (r>n) return 0;
  long long result = factorial(n);
  result *= fact_inv(r);
  result %= mod;
  result *= fact_inv(n-r);
  result %= mod;
  return result;
}
long long comb_inv(int n, int r) {
  assert(r>=0);
  assert(r<=n);
  long long result = fact_inv(n);
  result *= factorial(r);
  result %= mod;
  result *= factorial(n-r);
  result %= mod;
  return result;
}

// name: 一般化Catalan数
// prefix: fncatalan
// description: 反射原理による境界を越えない格子経路数
// cpp.json from here
// 一般化Catalan数（要：二項係数（階乗））
// long long catalan(int x1, int y1, int x2, int y2) :
//   (x1,y1)から(x2,y2)へ右・上に移動し、y<=xを保つ経路数を返す（mod）
// ※ x1<=x2、y1<=y2、y1<=x1、y2<=x2を満たさなければ0を返す
// ※ 0<=(x2-x1)+(y2-y1)<modであること
// ※ comb()によって階乗・逆階乗を不足時に自動拡張する
// ※ 元コード：ARC223 Dの解説ファイル
long long catalan(int x1, int y1, int x2, int y2) {
  if (x1>x2||y1>y2||y1>x1||y2>x2) return 0; 
  long long result = comb(x2-x1+y2-y1,y2-y1)-comb(x2-x1+y2-y1,x2-y1+1);
  result %= mod;
  if (result<0) result += mod;
  return result;
}
// cpp.json to here

int main () {

  // ABC205E White and Black Balls での使用例
  // https://atcoder.jp/contests/abc205/tasks/abc205_e
  // https://atcoder.jp/contests/abc205/submissions/80282580 （提出コードは階乗のコードが古い仕様）

  int n, m, k;
  cin >> n >> m >> k;

  long long result = catalan(0,-k,m,n-k);

  cout << result << endl;
  return 0;
}
