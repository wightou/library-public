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

// name: 約数列挙
// prefix: fndivisors
// description: 素因数分解による正の約数の列挙
// cpp.json from here
// 約数列挙（要：素因数分解どれか）
// 引数：約数列挙したい数
// 返り値：約数の一覧（sorted=trueなら昇順）
// 計算量：O(約数個数 * 素因数の種類数) + 素因数分解分 + ソートするならその分
template<class T>
vector<T> divisors(T n, bool sorted = false) {
  assert(n>0);
  vector<pair<T,int>> primes = prime_factorization(n);
  vector<T> result(1,1);
  for (auto [p,e] : primes) {
    int l = ssize(result);
    result.resize(l*(e+1),0);
    for (int i=0; i<l*e; i++) {
      result[i+l] = result[i]*p;
    }
  }
  if (sorted) sort(result.begin(),result.end());
  return result;
}
// cpp.json to here

int main () {

  // ABC180C Cream puff での使用例
  // https://atcoder.jp/contests/abc180/tasks/abc180_c
  // https://atcoder.jp/contests/abc180/submissions/80412244
  
  long long n;
  cin >> n;

  vector<long long> divs = divisors(n,true);

  for (size_t i=0; i<divs.size(); i++) {
    cout << divs.at(i) << endl;
  }

  return 0;

}
