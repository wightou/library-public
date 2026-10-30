#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 1001001001;

// name: Warshall-Floyd法
// prefix: fnwarshallfloyd
// description: 全頂点対の最短距離（負辺対応）
// cpp.json from here
// Warshall-Floyd法（負辺対応、負閉路の影響処理なし）
// 以下で、dはn×nの距離行列、nは頂点数
// void warshall_floyd(vector<vector<T>>& d) : 全頂点対の最短距離をdに上書きする、O(N^3)、追加空間O(1)
// ※ d[i][i]は0、辺がない頂点対はINF、辺がある場合はその重み（多重辺は最小値）で初期化する
// ※ 負閉路がある場合、負閉路の影響を受ける頂点対の最短距離は正しく求められない
// ※ 計算後、d[v][v]<0となる頂点が1つでもあれば負閉路が存在する
// ※ INFは有限の経路コストより十分大きく、距離の加算でTがオーバーフローしないことが必要
template<class T>
void warshall_floyd(vector<vector<T>>& d) {
  int n = d.size();
  for (int k=0; k<n; k++) {
    for (int i=0; i<n; i++) {
      for (int j=0; j<n; j++) {
        if (d[i][k]!=INF&&d[k][j]!=INF) d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
      }
    }
  }
}
// cpp.json to here

int main () {

  // ABC012 D バスと避けられない運命
  // https://atcoder.jp/contests/abc012/tasks/abc012_4
  // https://atcoder.jp/contests/abc012/submissions/80478377

  int n, m;
  cin >> n >> m;

  vector<int> a(m), b(m), t(m);
  for (int i=0; i<m; i++) {
    cin >> a.at(i) >> b.at(i) >> t.at(i);
    a.at(i)--;
    b.at(i)--;
  }

  vector<vector<int>> d(n,vector<int>(n,INF));
  for (int i=0; i<n; i++) {
    d.at(i).at(i) = 0;
  }
  for (int i=0; i<m; i++) {
    d.at(a.at(i)).at(b.at(i)) = min(d.at(a.at(i)).at(b.at(i)),t.at(i));
    d.at(b.at(i)).at(a.at(i)) = min(d.at(b.at(i)).at(a.at(i)),t.at(i));
  }

  warshall_floyd(d);

  int result = INF;
  for (int i=0; i<n; i++) {
    result = min(result,*max_element(d.at(i).begin(),d.at(i).end()));
  }

  cout << result << endl;

}
