#include <bits/stdc++.h>
using namespace std;

// name: 中央値
// prefix: fnmedian
// description: 2つのヒープによる中央値と絶対偏差和の管理
// cpp.json from here
// 中央値（2ヒープ方式）
// 以下で、Nは挿入済みの要素数
// Median() : 初期化、O(1)
// void emplace(long long x) : xを追加する、O(log N)
// long long value() : 中央値（偶数個なら小さい方）を返す、償却O(log N)
// long long diff() : 中央値からの絶対差の総和を返す、償却O(log N)
// ※ value()とdiff()はN>0で呼び出すこと
struct Median {
  priority_queue<long long> left;
  priority_queue<long long,vector<long long>,greater<long long>> right;
  long long sum_l = 0;
  long long sum_r = 0;
  void balance () {
    while (ssize(left)>ssize(right)+1) {
      sum_l -= left.top();
      sum_r += left.top();
      right.emplace(left.top());
      left.pop();
    }
    while (ssize(left)<ssize(right)) {
      sum_l += right.top();
      sum_r -= right.top();
      left.emplace(right.top());
      right.pop();
    }
  }
  void emplace(long long i) {
    if (left.empty()||i<left.top()) {
      left.emplace(i);
      sum_l += i;
    } else {
      right.emplace(i);
      sum_r += i;
    }
  }
  long long value() {
    assert(!left.empty());
    balance();
    return left.top();
  }
  long long diff() {
    long long num = value();
    return (ssize(left)*num-sum_l)+(sum_r-ssize(right)*num);
  }
};
// cpp.json to here

int main () {

  // ABC458D Chalkboard Median での使用例
  // https://atcoder.jp/contests/abc458/tasks/abc458_d
  // https://atcoder.jp/contests/abc458/submissions/80926495

  long long x;
  cin >> x;

  int q;
  cin >> q;

  Median med;
  med.emplace(x);

  for (int i=0; i<q; i++) {
    long long a, b;
    cin >> a >> b;
    med.emplace(a);
    med.emplace(b);
    cout << med.value() << '\n';
  }

  return 0;

}
