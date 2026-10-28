#include <bits/stdc++.h>
using namespace std;

// name: 平方数判定
// prefix: fnsquare
// description: 整数が平方数かどうかの判定
// cpp.json from here
// 平方数判定
// 引数：判定したい値
// 返り値：平方数かどうか
// 計算量：ほぼO(1)
bool is_square(long long n) {
  if (n<0) return false;
  if (n<2) return true;
  long long r = sqrtl(n);
  for (long long i=max(1LL,r-1); ; i++) {
    if (i>n/i) return false;
    if (i*i==n) return true;
  }
}
// cpp.json to here

int main () {

  // ABC086B 1 21 での使用例
  // https://atcoder.jp/contests/abc086/tasks/abc086_b
  // https://atcoder.jp/contests/abc086/submissions/80432664

  int a, b;
  cin >> a >> b;

  int tmp = stoi(to_string(a)+to_string(b));

  if (is_square(tmp)) cout << "Yes" << endl;
  else cout << "No" << endl;

  return 0;

}
