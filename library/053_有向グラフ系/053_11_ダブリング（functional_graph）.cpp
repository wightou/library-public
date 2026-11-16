#include <bits/stdc++.h>
using namespace std;

// name: ダブリング（Functional Graph）
// prefix: fndoubling
// description: 遷移先配列からダブリング表を必要に応じて構築
// cpp.json from here
// ダブリング（Functional Graph）
// 以下で、t[v]は頂点vからの遷移先、nは頂点数
// Doubling(const vector<int>& t) : 1回の遷移先を登録する、O(N)
// void make(int p) : 2^p回の遷移先までの表を構築する、O(N×新規構築段数)
// int jump(int v, long long k) : 頂点vからk回遷移した先を返す、O(log(k+1))+表の拡張分
// ※ n>=1、各t[v]は-1または0以上n未満を想定
// ※ t[v]==-1の場合は頂点vの自己ループとして扱う
// ※ table[p][v]は頂点vから2^p回遷移した先を表す
// ※ make()やjump()で必要に応じて表を拡張する
struct Doubling {
  int n;
  vector<vector<int>> table;
  Doubling(const vector<int>& t) {
    n = ssize(t);
    assert(n>0);
    table.emplace_back(t);
    for (int v=0; v<n; v++) {
      assert(-1<=table[0][v]&&table[0][v]<n);
      if (table[0][v]==-1) table[0][v] = v;
    }
  }
  void make(int p) {
    assert(p>=0);
    for (int i=ssize(table); i<=p; i++) {
      table.emplace_back(table[i-1]);
      for (int j=0; j<n; j++) table[i][j] = table[i-1][table[i][j]];
    }
  }
  int jump(int v, long long k) {
    assert(0<=v&&v<n);
    assert(k>=0);
    for (int j=0; k>0; j++) {
      if ((1LL<<j)&k) {make(j); v = table[j][v]; k -= (1LL<<j);}
    }
    return v;
  }
};
// cpp.json to here

int main () {

  // ABC167D Teleporter
  // https://atcoder.jp/contests/abc167/tasks/abc167_d
  // https://atcoder.jp/contests/abc167/submissions/80798150

  int n;
  long long k;
  cin >> n >> k;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
    a.at(i)--;
  }

  Doubling d(a);

  cout << d.jump(0,k)+1 << endl;

  return 0;

}
