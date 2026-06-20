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

int main() {
    int N,K;
    cin >> N >> K;

    vector<ll> L(N),R(N);
    rep(i,N) cin >> L[i] >> R[i];

    vector<pair<ll,ll>> RL(N);
    rep(i,N) RL[i] = {R[i],L[i]};
    sort(ALL(RL));
    
    rep(i,N){
        R[i] = RL[i].first;
        L[i] = RL[i].second;
    }

    ll ok = 0,ng = llinf;
    while(ng - ok > 1){
        ll m = (ng + ok) / 2;

        ll t = 0,nuno = 0;
        rep(i,N){
            if(i == 0){
                nuno++;
                t = R[i];
                continue;
            }
            if(t + m <= L[i]){
                nuno++;
                t = R[i];
            }
        }

        if(nuno >= K) ok = m;
        else ng = m;
    }

    if(ok == 0) cout << -1 << endl;
    else cout << ok << endl;
}