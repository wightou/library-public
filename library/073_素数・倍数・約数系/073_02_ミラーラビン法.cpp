#include <bits/stdc++.h>
using namespace std;

// name: 素数判定（ミラーラビン法）
// prefix: fnprimemr
// description: 64bit整数に対する決定的な素数判定
// cpp.json from here
// 素数判定（ミラーラビン法）
// 引数：素数判定する正整数
// 返り値：素数かどうかのbool値
// 計算量：O(log n) 
// ※ 1<=n<2^64
// ※ 7個の固定底を使用し、この範囲では決定的
__uint128_t power_mod_128(long long a, unsigned long long p, unsigned long long m) {
  a %= m;
  __uint128_t result = 1;
  __uint128_t b = a;
  while (p>0) {
    if (p&1LL) result = result*b%m;
    b = b*b%m;
    p >>= 1;
  }
  return result;
}
bool is_prime (unsigned long long n) {
  assert(n>0);
  if (n==1) return false;
  unsigned long long d = n-1;
  int s = 0;
  while ((d&1)==0) {s++; d >>= 1;}
  for (long long a : {2,325,9375,28178,450775,9780504,1795265022}) {
    if (a%n==0) continue;
    bool flag = false;
    __uint128_t num = power_mod_128(a,d,n);
    if (num==1) flag = true;
    for (int i=0; i<s; i++) {
      if (num+1==n) flag = true;
      num = num*num%n;
    }
    if (!flag) return false;
  }
  return true;
}
// cpp.json to here

int main () {

  // AWC0121 円形ネックレス での使用例
  // https://atcoder.jp/contests/awc0121/tasks/awc0121_c
  // https://atcoder.jp/contests/awc0121/submissions/80412124

  int q;
  cin >> q;

  for (int loop=0; loop<q; loop++) {

    long long n;
    cin >> n;

    for (int i=0; ; i++) {
      if (is_prime(n+i)) {
        cout << i << endl;
        break;
      }
    }

  }

  return 0;

}
