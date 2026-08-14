#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define onerep(i,n) for(int i = 1;i <= n;i++)

// 非負整数 x を a 進数で表したときの桁数を返す。0は1桁として扱う。
// 前提: a >= 2。
int keta(ll x,int a){
    assert(a >= 2);
    if(x == 0) return 1;
    int k = 0;
    while(x > 0){
        x /= a;
        k++;
    }
    return k;
}

// 繰り返し二乗法で a の b 乗を O(log b) で返す。前提: b >= 0。
ll pw(ll a,ll b){
    assert(b >= 0);
    ll res = 1;
    while(b > 0){
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

// 非負整数 x の a 進表記が回文なら true を返す。前提: a >= 2。
bool iskaibun(ll x,int a){
    int m = keta(x,a);
    bool flg = true;
    rep(i,m / 2) if((x / pw(a,i)) % a != (x / pw(a,m - i - 1)) % a) flg = false;
    return flg;
}

// 1～xを左半分として作れる、偶数桁・奇数桁の10進回文を重複なしで返す。
set<ll> make_kaibun(int x){
    set<ll> S;
    onerep(i,x){
        ll res1 = 0;
        ll res2 = 0;
        int k = keta(i,10);
        onerep(j,k){
            int p = static_cast<int>((i / pw(10,j - 1)) % 10);
            res1 += pw(10,k + j - 1) * p + pw(10,k - j) * p;
            if(j == 1) res2 += pw(10,k - j) * p;
            else res2 += pw(10,k + j - 2) * p + pw(10,k - j) * p;
        }
        S.insert(res1);
        S.insert(res2);
    }
    return S;
}
