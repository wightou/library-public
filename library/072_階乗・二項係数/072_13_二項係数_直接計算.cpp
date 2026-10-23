#include <bits/stdc++.h>
using namespace std;

// name: 二項係数（直接計算）
// prefix: fncomb4
// description: 剰余を用いない二項係数の直接計算
// cpp.json from here
// 二項係数（modなし）
// long long comb(long long n, long long r) : nCrを返す、O(min(r,n-r) log n)
// ※ n>=0、r<0またはr>nでは0を返す
// ※ 最終結果がlong longの範囲を超える場合は動作保証なし
long long comb(long long n, long long r) {
  assert(n>=0);
  if (r<0) return 0;
  if (r>n) return 0;
  r = min((long long)r,n-r);
  long long result = 1;
  for (long long i=0; i<r; i++) {
    long long g = gcd(n-i,i+1);
    result /= (i+1)/g;
    result *= (n-i)/g;
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC185C Duodecim Ferra での使用例
  // https://atcoder.jp/contests/abc185/tasks/abc185_c
  // https://atcoder.jp/contests/abc185/submissions/80282350

  int l;
  cin >> l;

  long long result = comb(l-1,11);

  cout << result << endl;

  return 0;

}
