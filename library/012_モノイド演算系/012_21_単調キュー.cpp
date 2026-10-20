#include <bits/stdc++.h>
using namespace std;

// name: 単調キュー
// prefix: fnmonoqueue
// description: 単調キュー
// cpp.json from here
// 単調キュー
// 以下で、vは値、lとpは位置
// コンストラクタ : MonoQueue(); : 準備、O(1)
// void emplace(T v, int p) : 単調キューにデータ{v,p}を入れる、償却O(1)
// void pop(int l) : 位置が l 以下のものを全て削除、償却O(1)
// pair<T,int> get() : 値と位置を返す、O(1)
// ※ compare()の内容はfirstの比較でaを消す条件に書き換えること
template<class T>
bool compare(T a, T b) {
  return (a<=b);
}
template<class T, bool(*compare)(T,T) = compare<T>>
struct MonoQueue {
  deque<pair<T,int>> que;
  MonoQueue() {}
  void emplace(T v, int p) {
    while (!que.empty()&&compare(que.back().first,v)) que.pop_back();
    que.emplace_back(v,p);
  }
  void pop(int l) {while (!que.empty()&&que.front().second<=l) que.pop_front();}
  pair<T,int> get() {assert(!que.empty()); return que.front();}
};
// cpp.json to here

template<class T>
bool compare2(T a, T b) {
  return (a>=b);
}

int main () {

  // AWC0001E 気温の変動幅 での使用例
  // https://atcoder.jp/contests/awc0001/tasks/awc0001_e
  // https://atcoder.jp/contests/awc0001/submissions/80223325

  int n, k;
  cin >> n >> k;

  vector<int> h(n);
  for (int i=0; i<n; i++) {
    cin >> h.at(i);
  }

  int result = 0;

  // 単調最大キュー
  MonoQueue<int> mono;

  // 単調最小キュー
  MonoQueue<int,compare2> mono2;

  for (int i=0; i<n; i++) {

    // 両方にデータを入れる
    mono.emplace(h.at(i),i);
    mono2.emplace(h.at(i),i);

    // 両方からはみ出た分を削除
    mono.pop(i-k);
    mono2.pop(i-k);

    // 値を取得して調査
    if (i>=k-1) result = max(result,mono.get().first-mono2.get().first);

  }

  cout << result << endl;

  return 0;

}