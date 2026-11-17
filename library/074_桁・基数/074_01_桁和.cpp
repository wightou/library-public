#include <bits/stdc++.h>
using namespace std;

// name: 桁和
// prefix: fndigitsum
// description: 10進・k進表記の整数の桁和
// cpp.json from here
// 桁和（10進・k進）
// long long digit_sum(long long n, long long k = 10) : nのk進法での各桁の和を返す、O(log(n+1))
long long digit_sum(long long n, long long k = 10) {
  assert(k>=2);
  assert(n>=0);
  long long result = 0;
  while (n>0) {
    result += n%k;
    n /= k;
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC083B Some Sums での使用例
  // https://atcoder.jp/contests/abc083/tasks/abc083_b
  //

  int n, a, b;
  cin >> n >> a >> b;

  int result = 0;
  for (int i=1; i<=n; i++) {
    int d = digit_sum(i);
    if (a<=d&&d<=b) result += i;
  }

  cout << result << endl;

  return 0;

}
