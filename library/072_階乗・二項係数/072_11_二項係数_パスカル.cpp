#include <bits/stdc++.h>
using namespace std;

constexpr int mod = 998244353;

// name: 二項係数（パスカル）
// prefix: fncomb2
// description: パスカルの三角形による二項係数計算
// cpp.json from here
// 二項係数（パスカルの三角形、modは素数でなくてもよい）
// int comb(int n, int r) : nCr mod modを返す
// ※ comb_dataを必要な行まで遅延生成、最大nまでの延べ計算量O(n^2)、メモリO(n^2)
// ※ n>=0、mod>=2、隣接2項の和がint型に収まること
vector<vector<int>> comb_data;
int comb(int n, int r) {
  if (r<0) return 0;
  if (r>n) return 0;
  int s = comb_data.size();
  if (s<=n) {
    comb_data.resize(n+1);
    if (s==0) {
      comb_data[0] = {1};
      s++;
    }
    while (s<=n) {
      comb_data[s].assign(s+1,0);
      comb_data[s][0] = 1;
      for (int j=1; j<s; j++) {
        comb_data[s][j] = (comb_data[s-1][j-1]+comb_data[s-1][j])%mod;
      }
      comb_data[s][s] = 1;
      s++;
    }
  }
  return comb_data[n][r];
}
// cpp.json to here

int main () {

  // ABC254B Practical Computing での使用例（最大値が998244353を超えないので、modを取っても問題ない）
  // https://atcoder.jp/contests/abc254/tasks/abc254_b
  // https://atcoder.jp/contests/abc254/submissions/80281738

  int n;
  cin >> n;

  vector<vector<int>> result(n);

  for (int i=0; i<n; i++) {
    for (int j=0; j<=i; j++) {
      result.at(i).emplace_back(comb(i,j));
    }
  }

  for (size_t j=0; j<result.size(); j++) {
    for (size_t i=0; i<result.at(j).size(); i++) {
      cout << result.at(j).at(i);
      if (i!=result.at(j).size()-1) {
        cout << " ";
      }
    }
    cout << endl;
  }

  return 0;

}
