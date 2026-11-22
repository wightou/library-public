#include <bits/stdc++.h>
using namespace std;

// name: 尺取法（tailベース）
// prefix: fnshakutoritail
// description: 右端を伸ばす尺取法。各左端に対する最大右端を計算し、結果を集計する
// cpp.json from here
// 尺取法（tailベース）
// vector<int> shakutori_detail<judge,add,remove>(int n, State& state, Args&&... args)
//   各tailに対し、条件を満たす最大の半開区間[tail,result[tail])の右端を返す
// long long shakutori<judge,add,remove>(int n, State& state, Args&&... args)
//   上記の右端配列を集計して返す（現在は条件を満たす区間の最大長）
// 計算量：O(N×(各操作の計算量の最大値))（judge、add、removeがO(1)ならO(N)）
// ※ stateは空区間を表す状態に初期化して渡す
// ※ judge(head,state,args...)は、現在の区間に要素headを追加しても条件を満たすか判定する（stateは変更しない）
// ※ add(head,state,args...)は右端に要素headを追加し、remove(tail,state,args...)は左端の要素tailを削除する
// ※ 各tailで、条件を満たす右端は連続し、その最大値はtailに関して単調非減少であること
// ※ 条件を満たす非空区間が存在しない場合はresult[tail]=tail。空区間ではremoveを呼ばない
// ※ args...は3関数のstate以降の引数に渡す
bool judge(int head, const int& dots, const string& s, int k) {
  return (dots+(s[head]=='.')<=k);
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
  for (int tail=0, head=0; tail<n; tail++) {
    while (head<n&&judge(head,state,args...)) {
      add(head,state,args...);
      head++;
    }
    result[tail] = head;
    if (tail<head) remove(tail,state,args...);
    else head = tail+1;
  }
  return result;
}
template<auto judge = judge, auto add = add_head, auto remove = remove_tail, class State, class... Args>
long long shakutori(int n, State& state, Args&&... args) {
  long long result = 0;
  vector<int> data = shakutori_detail<judge,add,remove>(n, state, args...);
  for (int tail=0; tail<n; tail++) {
    // result += data[tail]-tail;    // 条件を満たす非空区間の総数
    // result += n-data[tail];       // 条件を満たさない非空区間の総数
    result = max(result,(long long)data[tail]-tail); // 条件を満たす区間の最大長
  }
  return result;
}
// cpp.json to here

int main () {

  // ABC229D Longest X での使用例
  // https://atcoder.jp/contests/abc229/tasks/abc229_d
  // https://atcoder.jp/contests/abc229/submissions/81026229

  string s;
  int k;
  cin >> s >> k;

  int state = 0;
  cout << shakutori(ssize(s),state,s,k) << endl;

  return 0;

}
