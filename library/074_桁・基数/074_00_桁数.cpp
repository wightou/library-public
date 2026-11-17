#include <bits/stdc++.h>
using namespace std;

// name: 桁数
// prefix: fndigitcount
// description: 10進・k進表記の整数の桁数
// cpp.json from here
// 桁数（10進・k進）
// long long digit_count(long long n, long long k = 10) : nのk進法での桁数を返す、O(log(n+1))
// ※ n>0、k>=2
long long digit_count(long long n, long long k = 10) {
  assert(k>=2);
  assert(n>0);
  long long result = 0;
  while (n>0) {
    result++;
    n /= k;
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC156B Digits での使用例
  // https://atcoder.jp/contests/abc156/tasks/abc156_b
  // https://atcoder.jp/contests/abc156/submissions/80911369

  long long n, k;
  cin >> n >> k;

  long long result = digit_count(n,k);

  cout << result << endl;

  return 0;

}
