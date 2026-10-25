#include <bits/stdc++.h>
using namespace std;

// name: 素数判定（1つ）
// prefix: fnprime
// description: 試し割りによる単一の整数の素数判定
// cpp.json from here
// 素数判定
// 引数：素数判定する値
// 返り値：素数かどうかのbool値
// 計算量：O(√n)
// ※ 2^62まで（普通はそこまで行く前にTLEする）
bool is_prime (long long n) {
  if (n<2) return false;
  if (n%2==0&&n>2) return false;
  for (long long i=3; i*i<=n; i+=2) {
    if (n%i==0) return false;
  }
  return true;
}
// cpp.json to here

int main () {

  // アルゴリズムと数学012 Primality Test での使用例
  // https://atcoder.jp/contests/math-and-algorithm/tasks/math_and_algorithm_l
  // https://atcoder.jp/contests/math-and-algorithm/submissions/80394367

  long long n;
  cin >> n;

  string result = "No";

  if (is_prime(n)) result = "Yes";

  cout << result << endl;

  return 0;

}
