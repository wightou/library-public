#include <bits/stdc++.h>
using namespace std;

// name: トーシェント篩
// prefix: fntotients
// description: 篩によるトーシェント関数
// cpp.json from here
// 篩によるトーシェント関数
// 引数：トーシェント関数を求める正整数の上限
// 返り値：1以上n以下でnと互いに素な整数の個数の一覧
// 計算量：O(n)
vector<int> totient_list(int n) {
  assert(n>0);
  vector<int> result(n+1,1);
  iota(result.begin(),result.end(),0);
  for (int i=2; i<=n; i++) {
    if (result.at(i)!=i) continue;
    for (int j=i; j<=n; j+=i) {
      result[j] -= result[j]/i;
    }
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC162C Sum of gcd of Tuples (Easy) での使用例
  // https://atcoder.jp/contests/abc162/tasks/abc162_c
  // https://atcoder.jp/contests/abc162/submissions/80412267
  // （こんなややこしいことしなくても全探索で解ける）

  // k = Σ[d|k] φ(d) という式を利用すると、
  // Σ[k<=n] k *（kが最大公約数となる組数）= Σ[d<=n] φ(d) *（dが公約数となる組数）
  // となるので、それを利用する

  int k;
  cin >> k;

  int result = 0;

  vector<int> totient = totient_list(k);

  for (int i=1; i<=k; i++) {
    int m = k/i;
    result += totient.at(i)*m*m*m;
  }

  cout << result << endl;

  return 0;

}
