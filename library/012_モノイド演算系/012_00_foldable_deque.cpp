#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1001001001;

// name: Foldable Deque
// prefix: fnfolderble
// description: 累積保持deque
// cpp.json from here
// Foldable Deque
// 以下で、vは値、nは要素数
// コンストラクタ : foldable_deque(); : 空のDequeを用意、O(1)
// void emplace_front(const T& v) : 先頭にvを追加、償却O(1)
// void emplace_back(const T& v) : 末尾にvを追加、償却O(1)
// void pop_front() : 先頭の要素を削除、償却O(1)
// void pop_back() : 末尾の要素を削除、償却O(1)
// void reset() : 累積値を再構築、O(n)
// T prod() : 全要素のモノイド積を返す、O(1)
// int size() : 要素数を返す、O(1)
// bool empty() : 空かどうかを返す、O(1)
// ※ op()の内容は任意のモノイド（非可換でも可）に編集可（e()の編集も必要）
// ※ pop_front/backは空の場合には使用不可
template<class T>
T op(T a, T b) {
  return max(a,b);
}
template<class T>
T e() {
  return 0;
}
template<class T, T(*op)(T,T) = op<T>, T(*e)() = e<T>>
struct foldable_deque {
  int b = 0;
  deque<pair<T,T>> que;
  int size() const {return ssize(que);}
  bool empty() const {return que.empty();}
  void reset () {
    if (size()<2) return;
    b = size()/2;
    que[b].second = que[b].first;
    for (int i=b+1; i<size(); i++) que[i].second = op(que[i-1].second,que[i].first);
    que[b-1].second = que[b-1].first;
    for (int i=b-2; i>=0; i--) que[i].second = op(que[i].first,que[i+1].second);
  }
  void emplace_front (const T& value) {
    if (b==0) que.emplace_front(value,value);
    else que.emplace_front(value,op(value,que.front().second));
    b++;
  }
  void emplace_back (const T& value) {
    if (b==size()) que.emplace_back(value,value);
    else que.emplace_back(value,op(que.back().second,value));
  }
  void pop_front () {
    assert(size()>0);
    if (b==0) reset();
    que.pop_front();
    if (size()==0) b = 0;
    else b--;
  }
  void pop_back () {
    assert(size()>0);
    if (b==size()) reset();
    que.pop_back();
    if (size()==0) b = 0;
  }
  T prod () const {
    if (size()==0) return e();
    if (b==0) return que.back().second;
    if (b==size()) return que.front().second;
    return op(que.front().second,que.back().second);
  }
};
// cpp.json to here

template<class T>
T op2(T a, T b) {
  return min(a,b);
}
template<class T>
T e2() {
  return INF;
}

int main () {

  // ABC352D Permutation Subsequence での使用例
  // https://atcoder.jp/contests/abc352/tasks/abc352_d
  // https://atcoder.jp/contests/abc352/submissions/80449609

  int n, k;
  cin >> n >> k;

  vector<int> p(n);
  vector<int> p_inv(n);
  for (int i=0; i<n; i++) {
    cin >> p.at(i);
    p.at(i)--;
    p_inv.at(p.at(i)) = i;
  }

  // 最大値Foldable Dequeを用意
  foldable_deque<int> que1;

  // 最小値Foldable Dequeを用意
  foldable_deque<int,op2,e2> que2;

  int result = INF;

  // Foldable Dequeの後ろから入れ、前から捨てることで、sliding windowにする
  for (int i=0; i<n; i++) {
    que1.emplace_back(p_inv.at(i));
    que2.emplace_back(p_inv.at(i));
    if (i>=k) {
      que1.pop_front();
      que2.pop_front();
    }
    if (i>=k-1) result = min(result,que1.prod()-que2.prod());
  }

  cout << result << endl;

  return 0;

}
