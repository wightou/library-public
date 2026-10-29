#include <bits/stdc++.h>
using namespace std;

int main () {

  // name: 迷路入力（隣接リスト）
  // prefix: inmaze
  // description: 迷路を上下左右の無向グラフに変換\n#は壁、頂点番号は行*w+列\n座標は行・列の順で入力し、0-indexed化して保管
  // cpp.json from here
  int h, w, sx, sy, gx, gy;                                                       // snippet-replace: int ${1:h}, ${2:w}, ${3:sx}, ${4:sy}, ${5:gx}, ${6:gy};
  cin >> h >> w >> sx >> sy >> gx >> gy;                                          // snippet-replace: cin >> ${1} >> ${2} >> ${3} >> ${4} >> ${5} >> ${6};
  sx--;                                                                           // snippet-replace: ${3}--;
  sy--;                                                                           // snippet-replace: ${4}--;
  gx--;                                                                           // snippet-replace: ${5}--;
  gy--;                                                                           // snippet-replace: ${6}--;

  int s = sx*w+sy;                                                                // snippet-replace: int ${7:s} = ${3}*${2}+${4};
  int g = gx*w+gy;                                                                // snippet-replace: int ${8:g} = ${5}*${2}+${6};

  string maze_txt = "";                                                           // snippet-replace: string ${9:maze_txt} = "";
  for (int i=0; i<h; i++) {                                                       // snippet-replace: for (int i=0; i<${1}; i++) {
    string tmp;
    cin >> tmp;
    maze_txt += tmp;                                                              // snippet-replace: ${9} += tmp;
  }

  vector<vector<int>> maze(h*w);                                                  // snippet-replace: vector<vector<int>> ${10:maze}(${1}*${2});
  for (int i=0; i<h*w; i++) {                                                     // snippet-replace: for (int i=0; i<${1}*${2}; i++) {
    if (i<w*(h-1) && maze_txt.at(i)!='#' && maze_txt.at(i+w)!='#') {              // snippet-replace: if (i<${2}*(${1}-1) && ${9}.at(i)!='#' && ${9}.at(i+${2})!='#') {
      maze.at(i).emplace_back(i+w);                                               // snippet-replace: ${10}.at(i).emplace_back(i+${2});
      maze.at(i+w).emplace_back(i);                                               // snippet-replace: ${10}.at(i+${2}).emplace_back(i);
    }
    if (i%w<w-1 && maze_txt.at(i)!='#' && maze_txt.at(i+1)!='#') {                // snippet-replace: if (i%${2}<${2}-1 && ${9}.at(i)!='#' && ${9}.at(i+1)!='#') {
      maze.at(i).emplace_back(i+1);                                               // snippet-replace: ${10}.at(i).emplace_back(i+1);
      maze.at(i+1).emplace_back(i);                                               // snippet-replace: ${10}.at(i+1).emplace_back(i);
    }
  }
  // cpp.json to here

  cout << s << ' ' << g << '\n';
  for (int i=0; i<h*w; i++) {
    cout << i << ':';
    for (int to : maze.at(i)) cout << ' ' << to;
    cout << '\n';
  }

  return 0;
}
