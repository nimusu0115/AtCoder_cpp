#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// a,bはLLONG_MIN以外。中間係数と特殊解がlong longに収まる範囲で使う。

// 拡張ユークリッドの互除法。
// ax + by = gcd(a,b) を満たす係数を x,y に格納し、gcd(a,b) を返す。
long long extGCD(long long a, long long b, long long &x, long long &y) {
    assert(a != LLONG_MIN && b != LLONG_MIN);
    if (b == 0) {
        x = a < 0 ? -1 : 1;
        y = 0;
        return a < 0 ? -a : a;
    }

    long long x1, y1;
    long long g = extGCD(b, a % b, x1, y1);

    x = y1;
    __int128 next_y = static_cast<__int128>(x1) - static_cast<__int128>(a / b) * y1;
    assert(LLONG_MIN <= next_y && next_y <= LLONG_MAX);
    y = static_cast<long long>(next_y);

    return g;
}

// 一次不定方程式 ax + by = c の特殊解を x,y に、gcd(|a|,|b|)を g に格納する。
// 解が存在すれば true、存在しなければ false を返す。
bool solveDiophantine(long long a, long long b, long long c, long long &x, long long &y, long long &g) {
    assert(a != LLONG_MIN && b != LLONG_MIN);
    if (a == 0 && b == 0) {
        x = y = g = 0;
        return c == 0;
    }
    g = extGCD(abs(a), abs(b), x, y);

    if (c % g != 0) {
        return false;
    }

    long long scale = c / g;
    __int128 sx = static_cast<__int128>(x) * scale;
    __int128 sy = static_cast<__int128>(y) * scale;
    if (a < 0) sx = -sx;
    if (b < 0) sy = -sy;
    assert(LLONG_MIN <= sx && sx <= LLONG_MAX && LLONG_MIN <= sy && sy <= LLONG_MAX);
    x = static_cast<long long>(sx); y = static_cast<long long>(sy);

    return true;
}
