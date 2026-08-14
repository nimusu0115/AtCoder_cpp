#include<bits/stdc++.h>
using namespace std;
#define ll long long
// 原点から見た2次元ベクトル。cmpを使うと偏角の昇順に並べられる。
struct angsort{
  ll x;
  ll y;
};

// p と q の外積を返す。符号から反時計回り／時計回りの位置関係を判定できる。
// long long 同士の積であふれないよう、計算結果は __int128 とする。
__int128 cross(const angsort& p,const angsort& q){
  return (__int128)p.x * q.y - (__int128)q.x * p.y;
}

// ベクトルを上半平面(0)と下半平面(1)に分類する。ゼロベクトルだけは -1。
int half(const angsort& p){
  if(p.x == 0 && p.y == 0) return -1;
  return (p.y > 0 || (p.y == 0 && p.x >= 0)) ? 0 : 1;
}

// 原点を中心とした偏角で比較する関数。sortの第3引数として使用する。
// ゼロベクトルを先頭とし、正のx軸から反時計回りに並べる。
bool cmp(const angsort& p,const angsort& q){
  if(half(p) != half(q)) return half(p) < half(q);
  return cross(p,q) > 0;
}

// p と q が原点から同じ向きに伸びているかを返す。長さは一致しなくてもよい。
bool eql(const angsort& p,const angsort& q){
  return half(p) == half(q) && cross(p,q) == 0;
}
