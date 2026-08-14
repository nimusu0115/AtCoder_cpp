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
const ll MAX = 1'000'000'000;
set<ll> S,beki;

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

void solve(ll m){
    for(ll v : beki){
        ll nxt = v * pw(10,keta(m)) + m;
        if(keta(nxt) > 9) break;
        S.insert(nxt);
        solve(nxt);
    }
}

int main() {
    ll N;
    cin >> N;
    ll a = 1;
    while(a <= MAX){
        beki.insert(a);
        a *= 2;
    }

    solve(0);

    vector<ll> ans;
    for(auto v : S) ans.push_back(v);

    cout << ans[N - 1] << endl;
}