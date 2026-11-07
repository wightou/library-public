#include <bits/stdc++.h>
using namespace std;

// name: 閉路検出（関数グラフ）
// prefix: fnloopdetection
// description: 関数グラフの再訪までの頂点数と最初の再訪先を取得
// cpp.json from here
// 閉路検出（関数グラフ、非再帰）
// 以下で、t[v]は頂点vからの遷移先、nは頂点数
// pair<vector<int>,vector<int>> loop_detection(const vector<int>& t) : (dist,entry)を返す、O(N)
// ※ 0<=t[v]<nを想定（各頂点の出次数が1の有向グラフ）
// ※ dist[v]は頂点vから遷移を繰り返して、初めて再訪するまでに現れる異なる頂点の数
// ※ entry[v]は頂点vから遷移を繰り返したとき、最初に再訪する頂点
// ※ 閉路上の頂点vではentry[v]==v、dist[v]は閉路の長さとなる
pair<vector<int>,vector<int>> loop_detection(const vector<int>& t) {
  int n = ssize(t);
  vector<int> dist(n,0);
  vector<int> entry(n,-1);
  for (int i=0; i<n; i++) {
    if (dist[i]!=0) continue;
    int num = i;
    deque<int> que;
    while (dist[num]==0) {
      que.emplace_back(num);
      dist[num] = -ssize(que);
      num = t[num];
    }
    int value = dist[num]+1;
    if (value<=0) {
      value = ssize(que)+value;
      while (que.back()!=num) {
        dist[que.back()] = value;
        entry[que.back()] = que.back();
        que.pop_back();
      }
    }
    if (entry[num]!=-1) num = entry[num];
    while (!que.empty()) {
      dist[que.back()] = value;
      entry[que.back()] = num;
      que.pop_back();
      value++;
    }
  }
  return {dist,entry};
}
// cpp.json to here

int main () {

  // ABC357 E Reachability in Functional Graph
  // https://atcoder.jp/contests/abc357/tasks/abc357_e
  // https://atcoder.jp/contests/abc357/submissions/80638744

  int n;
  cin >> n;

  vector<int> a(n);
  for (int i=0; i<n; i++) {
    cin >> a.at(i);
    a.at(i)--;
  }

  auto [dist,entry] = loop_detection(a);

  cout << accumulate(dist.begin(),dist.end(),0LL) << endl;

  return 0;

}
