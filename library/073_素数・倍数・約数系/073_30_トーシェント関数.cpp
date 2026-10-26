#include <bits/stdc++.h>
using namespace std;

// 素因数分解
// 引数：素因数分解する値
// 返り値：「素数、指数」pairのvector
// 計算量：O(√n)
template<class T>
vector<pair<T,int>> prime_factorization(T n) {
  assert(n>0);
  vector<pair<T,int>> primes;
  long long p = 2;
  while (p*p<=n) {
    int counter = 0;
    while (n%p==0) {
      counter++;
      n /= p;
    }
    if (counter>0) primes.emplace_back(p,counter);
    if (p&1) p += 2;
    else p++;
  }
  if (n>1) primes.emplace_back(n,1);
  return primes;
}

// name: トーシェント関数（単発）
// prefix: fntotient
// description: オイラーのトーシェント関数
// cpp.json from here
// トーシェント関数（要：素因数分解どれか）
// 引数：トーシェント関数を求める正整数
// 返り値：1以上n以下でnと互いに素な整数の個数
// 計算量：O(log n) + 素因数分解分
// ※ n>0、n=1の場合は1を返す
long long totient(long long n) {
  assert(n>0);
  vector<pair<long long,int>> primes = prime_factorization(n);
  for (auto [p,_] : primes) {
    n /= p;
    n *= p-1;
  }
  return n;
}
// cpp.json to here

int main () {

  // ABC162C Sum of gcd of Tuples (Easy) での使用例
  // https://atcoder.jp/contests/abc162/tasks/abc162_c
  // https://atcoder.jp/contests/abc162/submissions/80412254
  // （こんなややこしいことしなくても全探索で解ける）

  // k = Σ[d|k] φ(d) という式を利用すると、
  // Σ[k<=n] k *（kが最大公約数となる組数）= Σ[d<=n] φ(d) *（dが公約数となる組数）
  // となるので、それを利用する

  int k;
  cin >> k;

  int result = 0;

  for (int i=1; i<=k; i++) {
    int m = k/i;
    result += totient(i)*m*m*m;
  }

  cout << result << endl;

  return 0;

}
