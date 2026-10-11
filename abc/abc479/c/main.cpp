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

int main() {
    ll N,W;
    cin >> N >> W;
    vector<ll> A(N),B(N);
    rep(i,N) cin >> A[i] >> B[i];

    ll ans = 0;
    rep(bit,pw(2,N)){
        ll del = 0,vol = 0;
        rep(i,N){
            if(((bit>>i) & 1) == 1){
                del += A[i];
                vol += B[i];
            }
        }
        if(vol <= W) chmax(ans,del);
    }

    cout << ans << endl;
}