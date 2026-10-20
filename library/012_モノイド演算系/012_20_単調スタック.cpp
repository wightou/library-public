#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1001001001;

// name: 単調スタック
// prefix: fnmonostack
// description: 単調スタック
// cpp.json from here
// 単調スタック
// 以下で、vは値、pは位置
// コンストラクタ : MonoStack(); : 準備、O(1)
// pair<T,int> emplace(T v, int p) : 単調スタックとして、直前の値を返しながら{v,p}を追加、償却O(1)
// 全消しした場合は{e(),-1}が返る
// ※ compare()の内容はfirstの比較でaを消す条件に書き換えること
// ※ e()は番兵としてその判定で全てに勝てるものを返すこと
template<class T>
bool compare(T a, T b) {
  return (a<=b);
}
template<class T>
T e() {
  return INF;
}
template<class T, bool(*compare)(T,T) = compare<T>, T(*e)() = e<T>>
struct MonoStack {
  deque<pair<T,int>> que;
  MonoStack() {que.emplace_back(e(),-1);}
  pair<T,int> emplace(T v, int p) {
    while (compare(que.back().first,v)) que.pop_back();
    pair<T,int> result = que.back();
    que.emplace_back(v,p);
    return result;
  }
};
// cpp.json to here

int main () {

  // ABC359E Water Tank での使用例
  // https://atcoder.jp/contests/abc359/tasks/abc359_e
  // https://atcoder.jp/contests/abc359/submissions/80223256

  int n;
  cin >> n;

  vector<int> h(n);
  for (int i=0; i<n; i++) {
    cin >> h.at(i);
  }

  vector<long long> dp(n,0);

  // 単調スタックを用意
  MonoStack<int> mono;

  // 追加しながら、返り値を見てDPテーブル更新
  for (int i=0; i<n; i++) {
    auto [v,p] = mono.emplace(h.at(i),i);
    if (p!=-1) dp.at(i) = dp.at(p);
    dp.at(i) += 1LL*h.at(i)*(i-p);
  }

  for (size_t i=0; i<dp.size(); i++) {
    cout << dp.at(i)+1;
    if (i!=dp.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;

}