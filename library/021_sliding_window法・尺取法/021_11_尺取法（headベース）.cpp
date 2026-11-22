#include <bits/stdc++.h>
using namespace std;

// name: 尺取法（headベース）
// prefix: fnshakutorihead
// description: 右端を1つ伸ばしてから左端を縮める尺取法。各右端に対する最小左端を計算し、結果を集計する
// cpp.json from here
// 尺取法（headベース）
// vector<int> shakutori_detail<judge,add,remove>(int n, State& state, Args&&... args)
//   各headに対し、条件を満たす最小の左端result[head]を返す（区間は[result[head],head+1)）
// long long shakutori<judge,add,remove>(int n, State& state, Args&&... args)
//   上記の左端配列を集計して返す
// 計算量：O(N×(各操作の計算量の最大値))（judge、add、removeがO(1)ならO(N)）
// ※ stateは空区間を表す状態に初期化して渡す
// ※ add(head,state,args...)は右端の要素headを追加する
// ※ judge(tail,state,args...)は現在の区間が条件を満たすときtrueを返す（stateは変更しない）
// ※ remove(tail,state,args...)は左端の要素tailを削除する
// ※ 各headで、条件を満たす左端は連続し、その最小値はheadに関して単調非減少であること
// ※ 条件を満たす非空区間が存在しない場合はresult[head]=head+1。空区間ではremoveを呼ばない
// ※ args...は3関数のstate以降の引数に渡す
// ※ 実行終了後のstateは通常、最後の有効区間を表す（空区間に戻るとは限らない）
bool judge(int, const int& dots, const string&, int k) {
  return (dots<=k);
}
void add_head(int head, int& dots, const string& s, int) {
  if (s[head]=='.') dots++;
}
void remove_tail(int tail, int& dots, const string& s, int) {
  if (s[tail]=='.') dots--;
}
template<auto judge = judge, auto add = add_head, auto remove = remove_tail, class State, class... Args>
vector<int> shakutori_detail(int n, State& state, Args&&... args) {
  assert(n>=0);
  vector<int> result(n);
  for (int head=0, tail=0; head<n; head++) {
    add(head,state,args...);
    while (tail<=head&&!judge(tail,state,args...)) {
      remove(tail,state,args...);
      tail++;
    }
    result[head] = tail;
  }
  return result;
}
template<auto judge = judge, auto add = add_head, auto remove = remove_tail, class State, class... Args>
long long shakutori(int n, State& state, Args&&... args) {
  long long result = 0;
  vector<int> data = shakutori_detail<judge,add,remove>(n, state, args...);
  for (int head=0; head<n; head++) {
    // result += head+1-data[head]; // 条件を満たす非空区間の総数
    // result += data[head];        // 条件を満たさない非空区間の総数
    result = max(result,(long long)head+1-data[head]); // 条件を満たす区間の最大長
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC229D Longest X での使用例
  // https://atcoder.jp/contests/abc229/tasks/abc229_d
  // https://atcoder.jp/contests/abc229/submissions/81026233

  string s;
  int k;
  cin >> s >> k;

  int state = 0;
  cout << shakutori(ssize(s),state,s,k) << endl;

  return 0;

}
