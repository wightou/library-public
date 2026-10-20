#include <bits/stdc++.h>
using namespace std;

int main () {

  vector<long long> a = {1,2,3,4,5};
  int n = ssize(a);

  // name: 一次元累積和スニペット
  // prefix: psum
  // description: 「より左」型一次元累積和
  // cpp.json from here
  vector<long long> sum(n+1,0);                  // snippet-replace: vector<long long> ${1:sum}(${3:n}+1,0);
  partial_sum(a.begin(),a.end(),sum.begin()+1);  // snippet-replace: partial_sum(${2:a}.begin(),${2}.end(),${1}.begin()+1);
  // cpp.json to here

  for (size_t i=0; i<sum.size(); i++) {
    cout << sum.at(i);
    if (i!=sum.size()-1) {
      cout << " ";
    }
  }
  cout << endl;

  return 0;

}