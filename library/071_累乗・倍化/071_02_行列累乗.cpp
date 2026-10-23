#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 1000000000;

// name: 行列積・行列累乗
// prefix: fnpowermatrix
// description: 行列積・単位行列・繰り返し二乗法による行列累乗
// cpp.json from here
// 行列積・単位行列・行列累乗（mod付き）
// vector<vector<long long>> prod(x,y) : n1行n2列のxとn2行n3列のyの積を返す、O(n1*n2*n3)
// vector<vector<long long>> e(int n) : n次の単位行列を返す、O(n^2)
// vector<vector<long long>> doubling(a,p) : 正方行列aのp乗を返す、O(n^3*log(p+1))
// ※ modは2以上2^31.5以下として外部で定義すること
// ※ 各行列は空でなく、各行の列数が等しいこと
// ※ 各要素は0以上mod未満であること
// ※ doubling()のpは非負であること
vector<vector<long long>> prod(const vector<vector<long long>>& x, const vector<vector<long long>>& y) {
  assert(!x.empty()&&!y.empty());
  int n1 = x.size();
  int n2 = x.at(0).size();
  assert(n2>0&&(int)y.size()==n2);
  int n3 = y.at(0).size();
  assert(n3>0);
  vector<vector<long long>> z(n1,vector<long long>(n3,0));
  for (int i=0; i<n1; i++) {
    for (int j=0; j<n3; j++) {
      for (int k=0; k<n2; k++) {
        z.at(i).at(j) += x.at(i).at(k)*y.at(k).at(j);
        z.at(i).at(j) %= mod;
      }
    }
  }
  return z;
}
vector<vector<long long>> e(int n) {
  assert(n>=1);
  vector<vector<long long>> result(n,vector<long long>(n,0));
  for (int i=0; i<n; i++) {
    result.at(i).at(i) = 1;
  }
  return result;
}
vector<vector<long long>> doubling(const vector<vector<long long>>& a, long long p) {
  assert(p>=0);
  assert(!a.empty()&&a.size()==a.at(0).size());
  if (p==0) {
    return e(a.size());
  } else if (p%2==0) {
    vector<vector<long long>> tmp = doubling(a,p/2);
    return prod(tmp,tmp);
  } else {
    vector<vector<long long>> tmp = doubling(a,p-1);
    return prod(tmp,a);
  }
}
// cpp.json to here

int main () {

  // アルゴリズムと数学054 Fibonacci Hard での使用例
  // https://atcoder.jp/contests/math-and-algorithm/tasks/math_and_algorithm_at
  // 

  long long n;
  cin >> n;

  vector<vector<long long>> mat = {{1,1},{1,0}};

  vector<vector<long long>> b = doubling(mat,n);

  cout << b.at(0).at(1) << '\n';

  return 0;

}
