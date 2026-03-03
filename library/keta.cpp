#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define onerep(i,n) for(int i = 1;i <= n;i++)

ll keta(ll x,int a){
    ll k = 0;
    while(x > 0){
        x /= a;
        k++;
    }
    return k;
}

ll pw(ll a,ll b){
    ll res = 1;
    while(b > 0){
        res *= a;
        b--;
    }
    return res;
}

bool iskaibun(ll x,int a){
    int m = keta(x,a);
    bool flg = true;
    rep(i,m / 2) if((x / pw(a,i)) % a != (x / pw(a,m - i - 1)) % a) flg = false;
    return flg;
}

set<ll> make_kaibun(int x){
    set<ll> S;
    onerep(i,x){
        ll res1 = 0;
        ll res2 = 0;
        int k = keta(i,10);
        onerep(j,k){
            int p = (i / pw(10,j - 1)) % 10;
            res1 += pw(10,k + j - 1) * p + pw(10,k - j) * p;
            if(j == 1) res2 += pw(10,k - j) * p;
            else res2 += pw(10,k + j - 2) * p + pw(10,k - j) * p;
        }
        S.insert(res1);
        S.insert(res2);
    }
    return S;
}