#include <bits/stdc++.h>
using namespace std;

// name: 素数判定（多数）
// prefix: fnprimes
// description: エラトステネスの篩による0からnまでの素数判定
// cpp.json from here
// エラトステネスの篩
// 引数：篩にかける上限値
// 返り値：iが素数かどうかをi番目に記録したvector<bool>
// 計算量：O(N*loglogN)
vector<bool> eratosthenes (int n) {
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
  return flags;
}
// cpp.json to here

int main () {

  // 競技プログラミングの鉄則A26 Prime Check での使用例
  // https://atcoder.jp/contests/tessoku-book/tasks/tessoku_book_z
  // https://atcoder.jp/contests/tessoku-book/submissions/80394389

  vector<bool> primes = eratosthenes(300000);

  int q;
  cin >> q;
  
  for (int loop=0; loop<q; loop++) {

    int n;
    cin >> n;
    if (primes.at(n)) cout << "Yes" << endl;
    else cout << "No" << endl;

  }
  
  return 0;

}
