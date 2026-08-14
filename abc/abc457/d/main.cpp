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
ll pw(ll a,ll b){
    ll res = 1;
    while(b > 0){
        res *= a;
        b--;
    }
    return res;
}

int main() {
    ll N,K;
    cin >> N >> K;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];

    ll ok = 1,ng = llinf * 2;
    while(ng - ok > 1){
        ll m = (ng - ok) / 2;
        m += ok;
        ll t = 0;
        rep(i,N) t += max(0LL,m - A[i] + i) / (i + 1);
        if(t <= K && t >= 0) ok = m;
        else ng = m;
    }

    cout << ok << endl;
}