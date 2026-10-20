#include <bits/stdc++.h>
using namespace std;

int main () {

  vector<vector<long long>> a = {{1,2,3,4,5},{6,7,8,9,0}};
  int h = ssize(a);
  int w = ssize(a.front());

  // name: 二次元累積和スニペット
  // prefix: psum2d
  // description: 「より左」型二次元累積和
  // cpp.json from here
  vector<vector<long long>> sum(h+1,vector<long long>(w+1,0));         // snippet-replace: vector<vector<long long>> ${1:sum}(${3:h}+1,vector<long long>(${4:w}+1,0));
  for (int i=0; i<h; i++) {                                            // snippet-replace: for (int i=0; i<${3}; i++) {
    partial_sum(a.at(i).begin(),a.at(i).end(),sum.at(i+1).begin()+1);  // snippet-replace: partial_sum(${2:a}.at(i).begin(),${2}.at(i).end(),${1}.at(i+1).begin()+1);
    for (int j=1; j<=w; j++) sum.at(i+1).at(j) += sum.at(i).at(j);     // snippet-replace: for (int j=1; j<=${4}; j++) ${1}.at(i+1).at(j) += ${1}.at(i).at(j);
  }
  // cpp.json to here

  for (size_t j=0; j<sum.size(); j++) {
    for (size_t i=0; i<sum.at(j).size(); i++) {
      cout << sum.at(j).at(i);
      if (i!=sum.at(j).size()-1) {
        cout << " ";
      }
    }
    cout << endl;
  }

  return 0;

}