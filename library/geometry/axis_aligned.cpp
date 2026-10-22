#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// 各軸の下端<上端の非退化な矩形/直方体を前提とする。
// 座標差はlong longに収まる範囲。overlapは離れていれば負になる。

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

// 共通体積。各軸の幅と最終体積がlong longに収まること。
// 積は範囲を確認しながら計算する（3軸を一度に掛けない）。
ll box_volume_from_widths(ll x, ll y, ll z) {
    if(x == 0 || y == 0 || z == 0) return 0;
    __int128 xy = static_cast<__int128>(x)*y;
    assert(xy <= numeric_limits<ll>::max());
    __int128 xyz = xy*z;
    assert(xyz <= numeric_limits<ll>::max());
    return static_cast<ll>(xyz);
}

// min={x下端,y下端,z下端}, max={x上端,y上端,z上端}。O(1)。
ll getIntersectionVolume(const ll min1[3], const ll max1[3], const ll min2[3], const ll max2[3]) {
    return box_volume_from_widths(
        max(0LL,min(max1[0],max2[0])-max(min1[0],min2[0])),
        max(0LL,min(max1[1],max2[1])-max(min1[1],min2[1])),
        max(0LL,min(max1[2],max2[2])-max(min1[2],min2[2])));
}

ll getIntersectionVolume3(const ll min1[3], const ll max1[3], const ll min2[3], const ll max2[3],
                          const ll min3[3], const ll max3[3]) {
    return box_volume_from_widths(
        max(0LL,min({max1[0],max2[0],max3[0]})-max({min1[0],min2[0],min3[0]})),
        max(0LL,min({max1[1],max2[1],max3[1]})-max({min1[1],min2[1],min3[1]})),
        max(0LL,min({max1[2],max2[2],max3[2]})-max({min1[2],min2[2],min3[2]})));
}
