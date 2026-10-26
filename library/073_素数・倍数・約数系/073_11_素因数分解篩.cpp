#include <bits/stdc++.h>
using namespace std;

// name: 素因数分解（多数）
// prefix: fnfactors
// description: エラトステネスの篩による素因数分解
// cpp.json from here
// エラトステネスの篩による素因数分解
// make_s_primes（事前の最小素因数篩）
// 引数：篩にかける上限値
// 返り値：なし
// 計算量：O(N*loglogN)
// prime_factorization（素因数分解）※ main内で事前にmake_s_primes()を呼ぶこと
// 引数：素因数分解する値
// 返り値：「素数、指数」pairのvector
// 計算量：O(logN)
vector<int> s_primes;
void make_s_primes (int n) {
  assert(n>=0);
  s_primes.assign(n+1,-1);
  bool flag = true;
  for (int i=2; i<=n; i++) {
    if (s_primes[i]!=-1) continue;
    s_primes[i] = i;
    if (!flag) continue;
    for (int j=i*i; j<=n; j+=i) {
      if (s_primes[j]==-1) s_primes[j] = i;
    }
    if (i*i>n) flag = false;
  }
}
template<class T>
vector<pair<T,int>> prime_factorization(T n) {
  assert(n>0);
  assert(n<ssize(s_primes));
  vector<pair<T,int>> result;
  while (n>1) {
    if (!result.empty()&&result.back().first==s_primes[n]) result.back().second++;
    else result.emplace_back(s_primes[n],1);
    n /= s_primes[n];
  }
  return result;
}
// cpp.json to here

int main () {
  
  // ABC177E Coprime での使用例
  // https://atcoder.jp/contests/abc177/tasks/abc177_e
  // https://atcoder.jp/contests/abc177/submissions/80412185

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  // 準備として最小素因数篩を用意
  make_s_primes(*max_element(a.begin(),a.end()));

  map<int,int> mp;

  for (int i : a) {
    vector<pair<int,int>> primes = prime_factorization(i);
    for (auto [p,e] : primes) {
      mp[p]++;
    }
  }

  bool flag1 = false;
  bool flag2 = false;

  for (auto [key,value] : mp) {
    if (value>1) flag1 = true;
    if (value==n) flag2 = true;
  }

  if (!flag1) cout << "pairwise coprime" << endl;
  else if (!flag2) cout << "setwise coprime" << endl;
  else cout << "not coprime" << endl;

  return 0;

}
