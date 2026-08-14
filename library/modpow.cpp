#include<bits/stdc++.h>
using namespace std;
#define ll long long

// aのb乗をmodで割った余りを繰り返し二乗法で返す。
// 計算量は O(log b)。前提: b >= 0、mod >= 1。
ll modpow(ll a,ll b,ll mod){
    assert(b >= 0 && mod >= 1);
    a %= mod;
    if(a < 0) a += mod;

    ll res = 1 % mod;
    while(b > 0){
        if(b & 1) res = static_cast<ll>((__int128)res * a % mod);
        a = static_cast<ll>((__int128)a * a % mod);
        b >>= 1;
    }
    return res;
}

// 素数modにおけるaの乗法逆元をフェルマーの小定理で返す。
// 前提: modは素数で、aはmodの倍数ではない。
ll modinv(ll a,ll mod){
    assert(mod >= 2 && a % mod != 0);
    return modpow(a,mod - 2,mod);
}
