#include <bits/stdc++.h>
using namespace std;

// name: 幅優先探索（簡易版）
// prefix: fnbfs
// description: 無重みグラフの幅優先探索による最短距離
// cpp.json from here
// 幅優先探索（簡易版）
// 以下で、graphは隣接リスト、startsは始点群、nは頂点数
// vector<int> bfs(const vector<vector<int>>& graph, const vector<int>& starts) : 各頂点への最短距離を返す、O(N+M)
// ※ 到達できない頂点の距離は-1
// ※ startsに同じ頂点を複数回指定することはできない
vector<int> bfs(const vector<vector<int>>& graph, const vector<int>& starts) {
  int n = ssize(graph);
  vector<int> distances(n,-1);
  deque<int> que;
  for (int v : starts) {
    assert(v>=0);
    assert(v<n);
    assert(distances[v]==-1);
    distances[v] = 0;
    que.emplace_back(v);
  }
  while (!que.empty()) {
    for (int v : graph[que.front()]) {
      if (distances[v]==-1) {
        distances[v] = distances[que.front()]+1;
        que.emplace_back(v);
      }
    }
    que.pop_front();
  }
  return distances;
}
// cpp.json to here

int main () {

  // ABC007C 幅優先探索
  // https://atcoder.jp/contests/abc007/tasks/abc007_3
  // https://atcoder.jp/contests/abc007/submissions/80466400

  int h, w, sx, sy, gx, gy;
  cin >> h >> w >> sx >> sy >> gx >> gy;
  sx--;
  sy--;
  gx--;
  gy--;

  int s = sx*w+sy;
  int g = gx*w+gy;

  string maze_txt = "";
  for (int i=0; i<h; i++){
    string tmp;
    cin >> tmp;
    maze_txt += tmp;
  }

  vector<vector<int>> maze(h*w);
  for (int i=0; i<h*w; i++){
    if (i<w*(h-1) && maze_txt.at(i)!='#' && maze_txt.at(i+w)!='#') {
      maze.at(i).emplace_back(i+w);
      maze.at(i+w).emplace_back(i);
    }
    if (i%w<w-1 && maze_txt.at(i)!='#' && maze_txt.at(i+1)!='#') {
      maze.at(i).emplace_back(i+1);
      maze.at(i+1).emplace_back(i);
    }
  }

  cout << bfs(maze,{s}).at(g) << endl;

  return 0;

}
