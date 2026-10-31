//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i,n) for(ll i = 0;i < n;i++)
#define rrep(i,n) for(ll i = n - 1;i >= 0;i--)
#define onerep(i,n) for(ll i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}
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

int main() {
    ll N,K;
    cin >> N >> K;

    ll k = K % pw(2,N);
    vector<vector<ll>> V;
    onerep(i,N){
        vector<ll> v(pw(2,i),0);
        V.push_back(v);
    }

    rep(i,N){
        if(i == 0){
            V[i][0] = (k + 1) / 2;
            V[i][1] = k / 2;
            continue;
        }
        rep(j,pw(2,i)){
            ll value = V[i - 1][j];
            V[i][2 * j] = (value + 1) / 2;
            V[i][2 * j + 1] =  value / 2;
        }
    }

    vector<ll> ans = V[N - 1];

    if(k == 0) cout << 0 << endl;
    else cout << 1 << endl;
    rep(i,pw(2,N)){
        cout << ans[i] + K / pw(2,N);
        if(i != pw(2,N) - 1) cout << " ";
    }
    cout << endl;
}