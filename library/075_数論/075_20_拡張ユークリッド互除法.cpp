#include <bits/stdc++.h>
using namespace std;

// name: 拡張ユークリッド互除法
// prefix: fnextgcd
// description: gcdとax+by=gcd(a,b)を満たす係数x,yを求める
// cpp.json from here
// 拡張ユークリッド互除法
// 引数：非負整数a,b、および係数を格納する参照x,y
// 返り値：gcd(a,b)。ax+by=gcd(a,b)となるx,yを設定
// 計算量：O(log(min(a,b)+1))
// ※ x,yには異なる変数を渡すこと
template<class T>
long long extend_gcd(long long a, long long b, T& x, T& y) {
  if (b==0) {
    x = 1;
    y = 0;
    return a;
  } else {
    long long d = extend_gcd(b,a%b,y,x);
    y -= a/b*x;
    return d;
  }
}
// cpp.json to here

int main () {

  // ABC186E Throne での使用例
  // https://atcoder.jp/contests/abc186/tasks/abc186_e
  // https://atcoder.jp/contests/abc186/submissions/80449593

  int q;
  cin >> q;

  for (int loop=0; loop<q; loop++) {

    int n, s, k;
    cin >> n >> s >> k;

    int g = gcd(gcd(n,s),k);
    n /= g;
    s /= g;
    k /= g;

    if (gcd(n,k)>1) {
      cout << -1 << endl;
      continue;
    }

    long long x,y;
    extend_gcd(n,k,x,y);
    y *= -s;
    y %= n;
    if (y<0) y += n;

    cout << y << endl;

  }

  return 0;

}
