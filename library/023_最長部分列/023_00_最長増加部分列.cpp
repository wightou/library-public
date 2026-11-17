#include <bits/stdc++.h>
using namespace std;

// name: 最長増加部分列
// prefix: fnlis
// description: 最長増加部分列の復元
// cpp.json from here
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
// cpp.json to here

int main () {

  // ABC006D トランプ挿入ソート での使用例
  // https://atcoder.jp/contests/abc006/tasks/abc006_4
  // https://atcoder.jp/contests/abc006/submissions/80910242

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  int result = n-ssize(lis(a));

  cout << result << endl;

  return 0;

}
