#include <bits/stdc++.h>
using namespace std;

// name: Sparse Table
// prefix: fnsparsetable
// description: 冪等なモノイドによる静的配列の区間処理
// cpp.json from here
// Sparse Table
// 以下で、aは元の配列、nは要素数、lとrは区間端
// コンストラクタ : SparseTable(const vector<T>& a); : 配列aからSparse Tableを構築する、O(N log N)
// T prod(int l, int r) : [l,r) の区間処理結果を返す、O(1)
// int size() : 要素数を返す、O(1)
// ※ op()の内容は任意の冪等なモノイド（非可換でも可）に編集可（e()の編集も必要）
// ※ 空区間のprod()はe()を返す
template<class T>
T op(T a, T b) {
  return max(a,b);
}
template<class T>
T e() {
  return 0;
}
template<class T, T(*op)(T,T) = op<T>, T(*e)() = e<T>>
struct SparseTable {
  vector<vector<T>> table;
  SparseTable(const vector<T>& a) {
    table.emplace_back(a);
    int i = 0;
    int d = 1;
    while (d*2<=size()) {
      table.emplace_back();
      for (int j=0; j+2*d<=size(); j++) table[i+1].emplace_back(op(table[i][j],table[i][j+d]));
      i++;
      d <<= 1;
    }
  }
  int size() const {return ssize(table.front());}
  T prod(int l, int r) const {
    assert(0<=l&&l<=r&&r<=size());
    if (l==r) return e();
    int i = bit_width((unsigned int)r-l)-1;
    return op(table[i][l],table[i][r-(1<<i)]);
  }
};
// cpp.json to here

int main () {

  // ABC134C Exception Handling での使用例（こんなものを用いなくてももっと簡単に解ける）
  // https://atcoder.jp/contests/abc134/tasks/abc134_c
  // https://atcoder.jp/contests/abc134/submissions/80450246

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
  }

  SparseTable<int> sp(a);

  for (int i=0; i<n; i++) cout << op(sp.prod(0,i),sp.prod(i+1,n)) << endl;

  return 0;

}
