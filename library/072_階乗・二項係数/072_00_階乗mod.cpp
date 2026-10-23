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

// name: 階乗mod
// prefix: fnfactorial
// description: 階乗と逆階乗のmod前計算
// cpp.json from here
// 階乗と逆階乗のmod計算（要：累乗mod）
// void make_factorial(int n) : nまでの階乗と逆階乗を前計算、不足分のみ追加、O(n) ※ log mod は定数扱いで
// long long factorial(int n) : n! modを返す、延べO(n_max) ※ log mod は定数扱いで
// long long fact_inv(int n) : n!の逆元modを返す、延べO(n_max) ※ log mod は定数扱いで
// ※ modは素数であること
// ※ factorial_data[i]はi! mod、fact_inv_data[i]はその逆元
// ※ factorial()とfact_inv()は0<=n<mod/2で使用すること
// ※ 未計算の場合は要求値の2倍まで階乗・逆階乗をまとめて計算する
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
  assert(n<mod/2);
  if (ssize(factorial_data)<=n) make_factorial(2*n);
  return factorial_data[n];
}
long long fact_inv(int n) {
  assert(n>=0);
  assert(n<mod/2);
  if (ssize(factorial_data)<=n) make_factorial(2*n);
  return fact_inv_data[n];
}
// cpp.json to here

int main () {

  // ABC055B Training Camp での使用例
  // https://atcoder.jp/contests/abc055/tasks/abc055_b

  int n;
  cin >> n;

  int result = factorial(n);

  cout << result << endl;

  return 0;

}
