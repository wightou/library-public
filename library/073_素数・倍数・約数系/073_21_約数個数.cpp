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

// name: 約数個数
// prefix: fndivcount
// description: 素因数分解による正の約数の個数
// cpp.json from here
// 約数個数（要：素因数分解どれか）
// 引数：約数個数を求める正整数
// 返り値：正の約数の個数
// 計算量：O(log n) + 素因数分解分
// ※ n>0、n=1の場合は1を返す
template<class T>
int div_count(T n) {
  assert(n>0);
  vector<pair<T,int>> primes = prime_factorization(n);
  int result = 1;
  for (auto [p,e] : primes) result *= e+1;
  return result;
}
// cpp.json to here

int main () {

  // ABC106B 105 での使用例
  // https://atcoder.jp/contests/abc106/tasks/abc106_b
  // https://atcoder.jp/contests/abc106/submissions/80412215

  int n;
  cin >> n;

  int result = 0;

  for (int i=1; i<=n; i+=2) {
    if (div_count(i)==8) result++;
  }

  cout << result << endl;

  return 0;

}
