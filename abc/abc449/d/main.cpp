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
ll L,R,D,U;
ll tate(ll l,ll r,ll d,ll u){
    if(l < L || R < l) return 0;
    return max(min(u,U) - max(d,D) + 1,0LL);
}
ll yoko(ll l,ll r,ll d,ll u){
    if(d < D || U < u) return 0;
    return max(min(r,R) - max(l,L) + 1,0LL);
}
int main() {
    cin >> L >> R >> D >> U;
    ll ans = 0;
    if(L <= 0 && 0 <= R && D <= 0 && 0 <= U) ans++;
    onerep(i,pow(10,6)){
        if(i % 2 == 1) continue;
        ll l = - i,r = - i,d = - i,u = i - 1;
        ans += tate(l,r,d,u);
        l = i,r = i,d = - i + 1,u = i;
        ans += tate(l,r,d,u);
        l = - i,r = i - 1,d = i,u = i;
        ans += yoko(l,r,d,u);
        l = - i + 1,r = i,d = - i,u = - i;
        ans += yoko(l,r,d,u);
    }
    cout << ans << endl;
}