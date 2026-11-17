#include <bits/stdc++.h>
using namespace std;

// name: 最長共通部分列
// prefix: fnlcs
// description: 動的計画法による最長共通部分列の復元
// cpp.json from here
// 最長共通部分列（動的計画法）
// vector<T> lcs(const vector<T>& s, const vector<T>& t) : 最長共通部分列を1つ復元して返す、O(MN)
template<class T>
vector<T> lcs(const vector<T>& s, const vector<T>& t) {
  int m = ssize(s);
  int n = ssize(t);
  vector<T> result;
  vector<vector<int>> dp(m+1,vector<int>(n+1,0));
  for (int i=1; i<=m; i++) {
    for (int j=1; j<=n; j++) {
      if (s[i-1]==t[j-1]) {
        dp[i][j] = dp[i-1][j-1]+1;
      } else {
        dp[i][j] = max(dp[i-1][j],dp[i][j-1]);
      }
    }
  }
  int i = m;
  int j = n;
  while (i>0&&j>0) {
    if (s[i-1]==t[j-1]) {
      i--;
      j--;
      result.emplace_back(s[i]);
    } else if (dp[i-1][j]==dp[i][j]) {
      i--;
    } else if (dp[i][j-1]==dp[i][j]) {
      j--;
    }
  }
  reverse(result.begin(),result.end());
  return result;
}
// cpp.json to here

int main () {

  // Educational DP Contest F LCS での使用例
  // https://atcoder.jp/contests/dp/tasks/dp_f
  // https://atcoder.jp/contests/dp/submissions/80910941

  string s, t;
  cin >> s >> t;

  vector<char> a(s.begin(),s.end());
  vector<char> b(t.begin(),t.end());

  vector<char> result = lcs(a,b);

  for (char c : result) cout << c;
  cout << '\n';

  return 0;

}
