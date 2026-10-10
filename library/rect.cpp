#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

// [l1, r1), [l2, r2) の重なりの長さ
ll overlap(ll l1, ll r1, ll l2, ll r2) {
    return min(r1, r2) - max(l1, l2);
}


// ====================
// 2D Rectangle
// ====================

struct Rect {
    ll l, r, d, u;
};

// 正の面積を持って重なる
bool intersect(const Rect& a, const Rect& b) {
    return overlap(a.l, a.r, b.l, b.r) > 0 &&
           overlap(a.d, a.u, b.d, b.u) > 0;
}

// 辺で接する（点だけの接触は含まない）
bool edge_touch(const Rect& a, const Rect& b) {
    ll x = overlap(a.l, a.r, b.l, b.r);
    ll y = overlap(a.d, a.u, b.d, b.u);

    return (x == 0 && y > 0) ||
           (x > 0 && y == 0);
}


// ====================
// 3D Box
// ====================

struct Box {
    ll x1, x2;
    ll y1, y2;
    ll z1, z2;
};

// 正の体積を持って重なる
bool intersect(const Box& a, const Box& b) {
    return overlap(a.x1, a.x2, b.x1, b.x2) > 0 &&
           overlap(a.y1, a.y2, b.y1, b.y2) > 0 &&
           overlap(a.z1, a.z2, b.z1, b.z2) > 0;
}

// 面で接する
bool face_touch(const Box& a, const Box& b) {
    ll x = overlap(a.x1, a.x2, b.x1, b.x2);
    ll y = overlap(a.y1, a.y2, b.y1, b.y2);
    ll z = overlap(a.z1, a.z2, b.z1, b.z2);

    return (x == 0 && y > 0 && z > 0) ||
           (x > 0 && y == 0 && z > 0) ||
           (x > 0 && y > 0 && z == 0);
}

// 辺で接する
bool edge_touch(const Box& a, const Box& b) {
    ll x = overlap(a.x1, a.x2, b.x1, b.x2);
    ll y = overlap(a.y1, a.y2, b.y1, b.y2);
    ll z = overlap(a.z1, a.z2, b.z1, b.z2);

    return (x > 0 && y == 0 && z == 0) ||
           (x == 0 && y > 0 && z == 0) ||
           (x == 0 && y == 0 && z > 0);
}

// 点で接する
bool point_touch(const Box& a, const Box& b) {
    ll x = overlap(a.x1, a.x2, b.x1, b.x2);
    ll y = overlap(a.y1, a.y2, b.y1, b.y2);
    ll z = overlap(a.z1, a.z2, b.z1, b.z2);

    return x == 0 && y == 0 && z == 0;
}