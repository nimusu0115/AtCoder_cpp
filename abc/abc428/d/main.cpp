#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'147'000'000;
const ll llinf = 9'223'000'000'000'000'000;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

ll keta(ll x){
    ll k = 0;
    while(x > 0){
        x /= 10;
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

ll sqrt_int(ll x){
    ll ok = 0,ng = inf;
    while(ok + 1 != ng){
        ll m = (ok + ng) / 2;
        if(m * m <= x) ok = m;
        else ng = m;
    }
    return ok;
}

ll solve(ll c,ll d){
    int keta_1 = keta(c + 1);
    int keta_d = keta(c + d);
    if(keta_1 == keta_d){
        ll begin = c * pw(10,keta_1) + c + 1;
        ll end = c * pw(10,keta_1) + c + d;
        ll res = sqrt_int(end) - sqrt_int(begin - 1);
        return res;
    }
    ll res = 0;
    rep(i,keta_d - keta_1 + 1){
        ll begin,end;
        if(i == 0){
            begin = c * pw(10,keta_1) + c + 1;
            end = c * pw(10,keta_1) + pw(10,keta_1) - 1;
        }
        else if(i == keta_d - keta_1){
            begin = c * pw(10,keta_d) + pw(10,keta_d - 1);
            end = c * pw(10,keta_d) + c + d;
        }
        else{
            begin = c * pw(10,keta_1 + i) + pw(10,keta_1 + i - 1);
            end = c * pw(10,keta_1 + i) + pw(10,keta_1 + i) - 1;
        }
        res += sqrt_int(end) - sqrt_int(begin - 1);
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        ll C,D;
        cin >> C >> D;

        cout << solve(C,D) << endl;
    }
}