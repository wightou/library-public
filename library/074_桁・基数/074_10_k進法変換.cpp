#include <bits/stdc++.h>
using namespace std;

// name: k進法変換
// prefix: fnbase
// description: 非負整数とk進法の各桁の配列との相互変換
// cpp.json from here
// k進法変換
// 以下で、nは元の整数、kは基数（k>=2）、各桁は下位桁から順に格納する
// vector<T> to_base(T n, T k) : nをk進法の桁配列に変換、O(log(n+1))
// T from_base(const vector<T>& n, T k) : k進法の桁配列から整数に復元、O(桁数)
// ※ to_base() はn>=0を想定し、n==0なら{0}を返す
// ※ from_base() は空配列を0として扱い、桁の値が0以上k未満でなくても形式的に計算する
// ※ Tは整数型とし、from_base() の途中計算と返り値はTの範囲内であること
template<class T>
vector<T> to_base(T n, T k) {
  assert(k>=2);
  assert(n>=0);
  if (n==0) return {0};
  vector<T> result;
  while (n>0) {
    result.emplace_back(n%k);
    n /= k;
  }
  return result;
}
template<class T>
T from_base(const vector<T>& n, T k) {
  assert(k>=2);
  T result = 0;
  for (int i=ssize(n)-1; i>=0; i--) {
    result *= k;
    result += n[i];
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC220B Base K での使用例
  // https://atcoder.jp/contests/abc220/tasks/abc220_b
  // https://atcoder.jp/contests/abc220/submissions/80939774

  int k;
  string sa, sb;
  cin >> k >> sa >> sb;

  vector<int> va, vb;
  for (char c : sa) va.emplace_back(c-'0');
  for (char c : sb) vb.emplace_back(c-'0');
  reverse(va.begin(),va.end());
  reverse(vb.begin(),vb.end());

  int a = from_base(va,k);
  int b = from_base(vb,k);

  cout << 1LL*a*b << endl;

  return 0;

}
