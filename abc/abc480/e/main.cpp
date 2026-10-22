//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

ll solve(ll x,ll y,ll N){
    ll ok = 0,ng = inf;
    while(ng - ok > 1){
        ll m = (ok + ng) / 2;

        ll n = N;
        ll p = y;
        rep(i,x){
            n /= p;
            p += m;
        }

        if(n > 0) ok = m;
        else ng = m;
    }

    return ok;
}

int main() {
    ll N;
    cin >> N;

    ll ans = 0;
    for(int i = 3;i < 20;i++){
        onerep(j,1000000){
            if(solve(i,j,N) == 0) break;
            ans += solve(i,j,N);
        }
    }

    cout << ans << endl;
}