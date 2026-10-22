#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 非負整数 x を a 進数で表したときの桁数を返す。0は1桁として扱う。
// 前提: a >= 2。
int keta(ll x,int a){
    assert(x >= 0 && a >= 2);
    if(x == 0) return 1;
    int k = 0;
    while(x > 0){
        x /= a;
        k++;
    }
    return k;
}

// 繰り返し二乗法で a の b 乗を O(log b) で返す。前提: b >= 0、結果はlong long内。
ll pw(ll a,ll b){
    assert(b >= 0);
    ll res = 1;
    while(b > 0){
        if(b & 1){
            __int128 value = static_cast<__int128>(res) * a;
            assert(LLONG_MIN <= value && value <= LLONG_MAX);
            res = static_cast<ll>(value);
        }
        b >>= 1;
        if(b){
            __int128 value = static_cast<__int128>(a) * a;
            assert(value <= LLONG_MAX);
            a = static_cast<ll>(value);
        }
    }
    return res;
}

// 非負整数 x の a 進表記が回文なら true を返す。前提: a >= 2。
bool iskaibun(ll x,int a){
    assert(x >= 0 && a >= 2);
    vector<int> digits;
    do { digits.push_back(static_cast<int>(x % a)); x /= a; } while(x);
    return equal(digits.begin(),digits.end(),digits.rbegin());
}

// 1～xを左半分として作れる、偶数桁・奇数桁の10進回文を重複なしで返す。
// long longに収まるものだけ返す。O(x log(x+1))時間・O(x)空間。
set<ll> make_kaibun(int x){
    assert(x >= 0);
    set<ll> S;
    for(ll left = 1; left <= x; ++left) for(bool odd : {false,true}){
        __int128 value = left;
        ll tail = odd ? left / 10 : left;
        while(tail){ value = value * 10 + tail % 10; tail /= 10; }
        if(value <= LLONG_MAX) S.insert(static_cast<ll>(value));
    }
    return S;
}
