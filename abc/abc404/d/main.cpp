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
    int N,M;
    cin >> N >> M;
    vector<ll> C(N);
    rep(i,N) cin >> C[i];
    vector<vector<int>> A(M);
    rep(i,M){
        int K;
        cin >> K;
        rep(j,K){
            int a;
            cin >> a;
            A[i].push_back(a - 1);
        }
    }

    ll ans = llinf;
    rep(i,pw(3,N)){
        ll cost = 0;
        vector<int> see(M,0);
        rep(j,N){
            int bit = (i / pw(3,j)) % 3;
            cost += bit * C[j];
            rep(k,M) for(auto v : A[k]) if(v == j) see[k] += bit;
        }
        bool flg = true;
        rep(j,M) if(see[j] < 2) flg = false;
        if(flg) chmin(ans,cost);
    }
    cout << ans << endl;
}