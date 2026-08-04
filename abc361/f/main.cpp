#include<bits/stdc++.h>
using namespace std;
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

ll prm[] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

ll pw(ll a,ll b){
    ll res = 1;
    while(b > 0){
        res *= a;
        b--;
    }
    return res;
}

ll polysq(ll x,ll p){
    ll ok = 1,ng = 1'000'000'010;
    while(ng - ok > 1){
        ll m = (ng + ok) / 2,k = x;
        rep(i,p) k /= m;
        if(k >= 1) ok = m;
        else ng = m;
    }
    return ok;
}

int main() {
    ll N;
    cin >> N;

    ll ans = 1;
    for(ll p : prm) ans += polysq(N,p) - 1;
    for(int i = 0;i < 16;i++){
        for(int j = i + 1;j < 17;j++){
            ans -= polysq(N,prm[i] * prm[j]) - 1;
        }
    }
    ans += polysq(N,2 * 3 * 5) - 1;
    ans += polysq(N,2 * 3 * 7) - 1;

    cout << ans << endl;
}