#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;

// name: 逆元列挙
// prefix: fninverselist
// description: 素数modにおける整数の乗法的逆元を必要に応じて列挙
// cpp.json from here
// 逆元列挙
// vector<long long> inverse_data : 添字iにiの逆元を格納する配列（0番目は便宜上0）
// void make_inverse(int n) : nまでの逆元を前計算する、O(n+1)（計算済みの部分は再計算しない）
// long long inverse(int n) : nの逆元を返す、計算済みならO(1)、未計算なら配列を拡張する
// 計算量 : 最大引数をN、関数の呼び出し回数をQとすると、全体でO(N+Q)、使用領域O(N+1)
// ※ modはint型で表現可能な素数として外部で定数または変数として定義し、使用途中で変更しないこと
// ※ 0<=n<modとする（inverse(0)は便宜上0を返す）
vector<long long> inverse_data = {0,1};
void make_inverse(int n) {
  assert(n>=0);
  assert(n<mod);
  int m = ssize(inverse_data);
  if (m>n) return;
  inverse_data.resize(n+1,1);
  for (int i=m; i<=n; i++) {
    inverse_data[i] = -inverse_data[mod%i]*(mod/i)%mod;
    if (inverse_data[i]<0) inverse_data[i] += mod;
  }
}
long long inverse(int n) {
  assert(n>=0);
  assert(n<mod);
  if (ssize(inverse_data)<=n) make_inverse(min(2LL*n,(long long)mod-1));
  return inverse_data[n];
}
// cpp.json to here

int main () {

  // ABC263E Sugoroku 3 での使用例
  // https://atcoder.jp/contests/abc263/tasks/abc263_e
  // https://atcoder.jp/contests/abc263/submissions/81111755

  int n;
  cin >> n;

  vector<int> a(n-1);
  for (int i=0; i<n-1; i++) {
    cin >> a.at(i);
  }

  long long result = 0;
  vector<long long> sum(n+1,0);

  for (int i=n-2; i>=0; i--) {
    result = ((sum.at(i+1)-sum.at(i+a.at(i)+1)+1)*inverse(a.at(i))+1)%mod;
    sum.at(i) = (sum.at(i+1)+result)%mod;
  }

  if (result<0) result += mod;
  cout << result << endl;

  return 0;

}
