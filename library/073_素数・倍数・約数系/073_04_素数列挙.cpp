#include <bits/stdc++.h>
using namespace std;

// name: 素数列挙
// prefix: fnplist
// description: エラトステネスの篩によるn以下の素数列挙
// cpp.json from here
// 素数列挙（エラトステネスの篩による）
// 引数：篩にかける上限値
// 返り値：n以下の素数一覧
// 計算量：O(N*loglogN)
vector<int> primes_list (int n) {
  assert(n>=0);
  vector<bool> flags(n+1,true);
  flags[0] = false;
  if (n>0) flags[1] = false;
  for (int i=2; i*i<=n; i++) {
    if (!flags[i]) continue;
    for (int j=i*i; j<=n; j+=i) {
      flags[j] = false;
    }
  }
  vector<int> result;
  for (int i=2; i<=n; i++) {
    if (flags[i]) result.emplace_back(i);
  }
  return result;
}
// cpp.json to here

int main () {

  // 競技プログラミングの鉄則B26 Output Prime Numbers での使用例
  // https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_cy
  // https://atcoder.jp/contests/tessoku-book/submissions/80412135

  int n;
  cin >> n;

  vector<int> result = primes_list(n);

  for (size_t i=0; i<result.size(); i++) {
    cout << result.at(i) << endl;
  }

  return 0;

}
