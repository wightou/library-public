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

// name: 約数総和
// prefix: fndivsum
// description: 素因数分解による正の約数の総和
// cpp.json from here
// 約数総和（要：素因数分解どれか）
// 引数：約数総和を求める正整数
// 返り値：正の約数の総和
// 計算量：O(log n) + 素因数分解分
// ※ n>0、n=1の場合は1を返す
// ※ 返り値がlong longに収まること
long long div_sum(long long n) {
  assert(n>0);
  vector<pair<long long,int>> primes = prime_factorization(n);
  long long result = 1;
  for (auto [p,e] : primes) {
    long long tmp = 1;
    long long r = 1;
    for (int i=0; i<e; i++) {
      r *= p;
      tmp += r;
    }
    result *= tmp;
  }
  return result;
}
// cpp.json to here

int main () {

  // ARC026B 完全数 での使用例
  // https://atcoder.jp/contests/arc026/tasks/arc026_2
  // https://atcoder.jp/contests/arc026/submissions/80412237

  long long n;
  cin >> n;

  long long sum = div_sum(n)-n;

  if (sum<n) cout << "Deficient" << endl;
  else if (sum>n) cout << "Abundant" << endl;
  else cout << "Perfect" << endl;

  return 0;

}
