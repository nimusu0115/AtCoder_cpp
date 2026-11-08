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

ll op_max(ll a,ll b){
    return max(a,b);
}

ll op_min(ll a,ll b){
    return min(a,b);
}

ll e_max(){
    return -llinf;
}
ll e_min(){
    return llinf;
}

int main() {
    ll N;
    cin >> N;
    vector<ll> A(N),pos(N + 1,0);
    rep(i,N) cin >> A[i];

    onerep(i,N) pos[i] = pos[i - 1] +  A[i - 1];

    segtree<ll,op_max,e_max> seg_max(pos);
    segtree<ll,op_min,e_min> seg_min(pos);

    ll ans = seg_max.all_prod() - seg_min.all_prod();
    rep(i,N){
        ll lmax = seg_max.prod(0,i + 1);
        ll lmin = seg_min.prod(0,i + 1);
        ll rmax = seg_max.prod(i + 2,N + 1) - pos[i + 1];
        ll rmin = seg_min.prod(i + 2,N + 1) - pos[i + 1];
        if(i == N - 1) rmax = 0,rmin = 0;
        if(A[i] < 0) A[i] *= -1;
        ll p = max(lmax,pos[i] + A[i] + rmax) - min(lmin,pos[i] + A[i] + rmin);
        ll m = max(lmax,pos[i] - A[i] + rmax) - min(lmin,pos[i] - A[i] + rmin);
        chmax(ans,max(p,m) + 1);
        //cout << i << " " << max(lmax,pos[i] - A[i] + rmax) << " " << min(lmin,pos[i] - A[i] + rmin) << endl;
        //cout << rmax << " " << rmin << endl;
    }

    cout << ans << endl;
}