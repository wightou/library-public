#include <bits/stdc++.h>
using namespace std;

// name: ベクトル（図形）
// prefix: point
// description: 二次元整数座標の点・ベクトル演算と位置関係の判定
// cpp.json from here
// ベクトル（図形）
// 以下、a,b,c,dはPoint型の点。すべての関数の計算量はO(1)
// 前提：Pointの座標演算・座標差はlong longの範囲内
//       64bitの整数演算は途中結果もlong longの範囲内
//       dot128・cross128の途中結果は__int128_tの範囲内
// Point : 二次元整数座標(x,y)。四則演算・等値比較・辞書順比較に対応
// Point::norm2() : 原点からの距離の2乗（long long）
// Point::norm() : 原点からの距離（long double。内部でnorm2()を使用）
// Pointの除算 : 各座標を整数除算（除数は0以外）
// is_zero(a) : aが零ベクトルか判定
// dot(a,b), dot128(a,b) : ベクトルa,bの内積（long long / __int128_t）
// dot(a,b,c), dot128(a,b,c) : (b-a)と(c-a)の内積
// is_front(a,b,c) : (b-a)と(c-a)の内積が正か判定
// is_perpendicular(a,b,c) : (b-a)と(c-a)の内積が0か判定
// is_back(a,b,c) : (b-a)と(c-a)の内積が負か判定
// cross(a,b), cross128(a,b) : ベクトルa,bの外積（long long / __int128_t）
// cross(a,b,c), cross128(a,b,c) : (b-a)と(c-a)の外積
// is_left(a,b,c) : 有向直線abの左側にcがあるか判定
// is_straight(a,b,c) : a,b,cが一直線上にあるか判定
// is_right(a,b,c) : 有向直線abの右側にcがあるか判定
// is_on_segment(a,b,c) : cが閉線分ab上にあるか判定（端点を含む）
// is_parallel(a,b) : ベクトルa,bの外積が0か判定
// is_parallel(a,b,c,d) : (b-a)と(d-c)の外積が0か判定
// is_opposite_side(a,b,c,d) : c,dが直線abの厳密に反対側にあるか判定
// is_strict_intersect(a,b,c,d) : 線分abとcdが端点以外で交差するか判定（重なる場合はfalse）
// is_intersect(a,b,c,d) : 線分abとcdが交差するか判定（端点接触・重なりを含む）
// distance(a,b,c) : 点cと直線abの距離（long double。a!=b、内部は64bit外積）
struct Point {
  long long x = 0;
  long long y = 0;
  long long norm2() const {
    return (x*x+y*y);
  }
  long double norm() const {
    return sqrtl(norm2());
  }
  Point operator-() const {
    return {-x,-y};
  }
  Point operator+(const Point& other) const {
    return {x+other.x,y+other.y};
  }
  Point operator-(const Point& other) const {
    return {x-other.x,y-other.y};
  }
  Point operator*(long long other) const {
    return {x*other,y*other};
  }
  Point operator/(long long other) const {
    assert(other!=0);
    return {x/other,y/other};
  }
  void operator+=(const Point& other) {
    x += other.x;
    y += other.y;
  }
  void operator-=(const Point& other) {
    x -= other.x;
    y -= other.y;
  }
  void operator*=(long long other) {
    x *= other;
    y *= other;
  }
  void operator/=(long long other) {
    assert(other!=0);
    x /= other;
    y /= other;
  }
  bool operator==(const Point& other) const {
    return (x==other.x&&y==other.y);
  }
  bool operator!=(const Point& other) const {
    return (x!=other.x||y!=other.y);
  }
  bool operator<(const Point& other) const {
    return (x<other.x||(x==other.x&&y<other.y));
  }
};
bool is_zero(const Point& a) {return (a.x==0&&a.y==0);}
long long dot(const Point& a, const Point& b) {return a.x*b.x+a.y*b.y;}
__int128_t dot128(const Point& a, const Point& b) {return (__int128)1*a.x*b.x+(__int128)1*a.y*b.y;}
long long dot(const Point& a, const Point& b, const Point& c) {return dot(b-a, c-a);}
__int128_t dot128(const Point& a, const Point& b, const Point& c) {return dot128(b-a, c-a);}
bool is_front(const Point& a, const Point& b, const Point& c) {return (dot128(a,b,c)>0);}
bool is_perpendicular(const Point& a, const Point& b, const Point& c) {return (dot128(a,b,c)==0);}
bool is_back(const Point& a, const Point& b, const Point& c) {return (dot128(a,b,c)<0);}
long long cross(const Point& a, const Point& b) {return a.x*b.y-a.y*b.x;}
__int128_t cross128(const Point& a, const Point& b) {return (__int128)1*a.x*b.y-(__int128)1*a.y*b.x;}
long long cross(const Point& a, const Point& b, const Point& c) {return cross(b-a, c-a);}
__int128_t cross128(const Point& a, const Point& b, const Point& c) {return cross128(b-a, c-a);}
bool is_left(const Point& a, const Point& b, const Point& c) {return (cross128(a,b,c)>0);}
bool is_straight(const Point& a, const Point& b, const Point& c) {return (cross128(a,b,c)==0);}
bool is_right(const Point& a, const Point& b, const Point& c) {return (cross128(a,b,c)<0);}
bool is_on_segment(const Point& a, const Point& b, const Point& c) {return (is_straight(a,b,c)&&!is_front(c,a,b));}
bool is_parallel(const Point& a, const Point& b) {return (cross128(a,b)==0);}
bool is_parallel(const Point& a, const Point& b, const Point& c, const Point& d) {return (cross128(b-a,d-c)==0);}
bool is_opposite_side(const Point& a, const Point& b, const Point& c, const Point& d) {return ((is_left(a,b,c)&&is_right(a,b,d))||(is_left(a,b,d)&&is_right(a,b,c)));}
bool is_strict_intersect(const Point& a, const Point& b, const Point& c, const Point& d) {return (is_opposite_side(a,b,c,d)&&is_opposite_side(c,d,a,b));}
bool is_intersect(const Point& a, const Point& b, const Point& c, const Point& d) {return (is_strict_intersect(a,b,c,d)||is_on_segment(a,b,c)||is_on_segment(a,b,d)||is_on_segment(c,d,a)||is_on_segment(c,d,b));}
long double distance(const Point& a, const Point& b, const Point& c) {return abs(cross(a,b,c))/(b-a).norm();}
// cpp.json to here

int main () {

  // ABC266C Convex Quadrilateral での使用例
  // https://atcoder.jp/contests/abc266/tasks/abc266_c
  // https://atcoder.jp/contests/abc266/submissions/80928773

  // point型を用意する
  Point a, b, c, d;
  cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;

  string result = "Yes";

  // 外積を利用した判定をする
  if (!is_right(a,d,b)) result = "No";
  if (!is_right(b,a,c)) result = "No";
  if (!is_right(c,b,d)) result = "No";
  if (!is_right(d,c,a)) result = "No";

  cout << result << endl;

  return 0;

}
