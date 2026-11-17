#include <bits/stdc++.h>
using namespace std;

// 最長増加部分列（狭義）
// vector<T> lis(const vector<T>& original) : 最長増加部分列を1つ復元して返す、O(N log N)
// ※ 広義単調増加部分列の場合はlower_boundをupper_boundに変更する
template<class T>
vector<T> lis(const vector<T>& original) {
  int n = ssize(original);
  if (n==0) return {};
  vector<int> len(n);
  vector<T> vec;
  vec.reserve(n);
  for (int i=0; i<n; i++) {
    len[i] = lower_bound(vec.begin(),vec.end(),original[i])-vec.begin();
    if (len[i]==ssize(vec)) vec.emplace_back(original[i]);
    else vec[len[i]] = original[i];
  }
  vector<T> result(ssize(vec));
  int idx = ssize(vec)-1;
  for (int i=n-1; i>=0; i--) {
    if (len[i]==idx) {
      result[idx] = original[i];
      idx--;
    }
  }
  return result;
}

// name: 最長共通部分列（LIS利用）
// prefix: fnlcs2
// description: LIS利用による最長共通部分列の復元
// cpp.json from here
// 最長共通部分列（LIS利用、要：最長増加部分列）
// 以下で、MとNはそれぞれsとtの長さ、Kは値が一致する添字の組数
// vector<T> lcs(const vector<T>& s, const vector<T>& t) : 最長共通部分列を1つ復元して返す、O((M+N)log(M+N)+K log(K+1))
template<class T>
vector<T> lcs(const vector<T>& s, const vector<T>& t) {
  int m = ssize(s);
  int n = ssize(t);
  map<T,vector<int>> mp;
  for (int i=m-1; i>=0; i--) mp[s[i]].emplace_back(i);
  vector<int> vec;
  for (int j=0; j<n; j++) {
    auto it = mp.find(t[j]);
    if (it!=mp.end()) for (int i : (*it).second) vec.emplace_back(i);
  }
  vector<int> vec2 = lis(vec);
  vector<T> result(ssize(vec2));
  for (int i=0; i<ssize(vec2); i++) result[i] = s[vec2[i]];
  return result;
}
// cpp.json to here

int main () {

  // Educational DP Contest F LCS での使用例
  // https://atcoder.jp/contests/dp/tasks/dp_f
  // https://atcoder.jp/contests/dp/submissions/80911008

  string s, t;
  cin >> s >> t;

  vector<char> a(s.begin(),s.end());
  vector<char> b(t.begin(),t.end());

  vector<char> result = lcs(a,b);

  for (char c : result) cout << c;
  cout << '\n';

  return 0;

}
