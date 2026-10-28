#include <bits/stdc++.h>
using namespace std;

// name: Disjoint Sparse Table
// prefix: fndisjointsparsetable
// description: 任意のモノイドによる静的配列の区間処理
// cpp.json from here
// Disjoint Sparse Table
// 以下で、aは元の配列、nは要素数、lとrは区間端
// コンストラクタ : DisjointSparseTable(const vector<T>& a); : 配列aからDisjoint Sparse Tableを構築する、O(N log N)
// T prod(int l, int r) : [l,r) の区間処理結果を返す、O(1)
// int size() : 要素数を返す、O(1)
// ※ op()の内容は任意のモノイド（非可換でも可）に編集可（e()の編集も必要）
// ※ 空区間のprod()はe()を返す
template<class T>
T op(T a, T b) {
  return a+b;
}
template<class T>
T e() {
  return 0;
}
template<class T, T(*op)(T,T) = op<T>, T(*e)() = e<T>>
struct DisjointSparseTable {
  vector<vector<T>> table;
  DisjointSparseTable(const vector<T>& a) {
    table.emplace_back(a);
    int i = 1;
    int d = 2;
    while (d<size()) {
      table.emplace_back(table[0]);
      for (int b=d; b<size(); b+=2*d) {
        for (int j=b+1; j<min(b+d,size()); j++) table[i][j] = op(table[i][j-1],table[0][j]);
        for (int j=b-2; j>=b-d; j--) table[i][j] = op(table[0][j],table[i][j+1]);
      }
      i++;
      d <<= 1;
    }
  }
  int size() const {return ssize(table[0]);}
  T prod(int l, int r) const {
    assert(0<=l&&l<=r&&r<=size());
    if (l==r) return e();
    if (r-l==1) return table[0][l];
    int i = bit_width((unsigned int)(l^(r-1)))-1;
    return op(table[i][l],table[i][r-1]);
  }
};
// cpp.json to here

int main () {

  // 典型90問010 Score Sum Queries での使用例（こんなものを用いなくても累積和で解ける）
  // https://atcoder.jp/contests/typical90/tasks/typical90_j
  // https://atcoder.jp/contests/typical90/submissions/80450602

  int n;
  cin >> n;

  vector<int> c(n), p(n);
  for (int i=0; i<n; i++) {
    cin >> c.at(i) >> p.at(i);
  }

  vector<int> p1(n,0);
  vector<int> p2(n,0);
  for (int i=0; i<n; i++) {
    if (c.at(i)==1) p1.at(i) = p.at(i);
    else p2.at(i) = p.at(i);
  }

  // Disjoint Sparse Tableのデータを、1組分と2組分を用意する
  DisjointSparseTable<int> dst1(p1);
  DisjointSparseTable<int> dst2(p2);

  int q;
  cin >> q;

  for (int loop=0; loop<q; loop++) {

    int l, r;
    cin >> l >> r;
    l--;
    r--;

    // 処理をして、出力
    cout << dst1.prod(l,r+1) << " " << dst2.prod(l,r+1) << endl;

  }

  return 0;
}
