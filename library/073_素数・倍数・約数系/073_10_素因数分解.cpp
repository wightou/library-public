#include <bits/stdc++.h>
using namespace std;

// name: 素因数分解（1つ）
// prefix: fnfactor
// description: 試し割りによる単一の整数の素因数分解
// cpp.json from here
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
// cpp.json to here

int main () {

  // ABC169D Div Game での使用例
  // https://atcoder.jp/contests/abc169/tasks/abc169_d
  // https://atcoder.jp/contests/abc169/submissions/80412153

  long long n;
  cin >> n;

  vector<pair<long long,int>> primes = prime_factorization(n);

  int result = 0;

  for (auto [p,e] : primes) {
    for (int i=1; i<=e; i++) {
      result++;
      e -= i;
    }
  }

  cout << result << endl;

  return 0;

}
