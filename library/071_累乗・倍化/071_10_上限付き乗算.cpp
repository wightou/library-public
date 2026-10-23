#include <bits/stdc++.h>
using namespace std;

constexpr long long INF = 1000000000000000001LL;

// name: 上限付き乗算
// prefix: fnprodlimit
// description: オーバーフローを防ぎ積を[-INF,INF]に制限する乗算
// cpp.json from here
// 上限付き乗算
// long long prod(long long x, long long y) : max(-INF,min(x*y,INF))を返す、O(1)
// ※ INFは外部で正の値として定義すること（2*INF<2^63）
// ※ x,yはLLONG_MIN以外のlong longとすること（符号を除いた絶対値をlong longで扱うため）
long long prod (long long x, long long y) {
  if (x==0||y==0) return 0;
  int sign_x = (x>0)*2-1;
  x *= sign_x;
  int sign_y = (y>0)*2-1;
  y *= sign_y;
  if (2*INF/x<y) return INF*sign_x*sign_y;
  if (x*y>INF) return INF*sign_x*sign_y;
  return x*y*sign_x*sign_y;
}
// cpp.json to here

int main () {

  // ABC169B - Multiplication 2 での使用例
  // https://atcoder.jp/contests/abc169/tasks/abc169_b
  // https://atcoder.jp/contests/abc169/submissions/80280135

  int n;
  cin >> n;

  vector<long long> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  long long result = 1;
  for (long long i : a) {
    result = prod(result,i);
  }

  if (result==INF) result = -1;

  cout << result << endl;

  return 0;

}
