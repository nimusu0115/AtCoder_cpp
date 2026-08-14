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
    ll N,K;
    cin >> N >> K;
    vector<vector<ll>> A(N);
    vector<ll> L(N);
    rep(i,N){
        cin >> L[i];
        rep(j,L[i]){
            ll a;
            cin >> a;
            A[i].push_back(a);
        }
    }

    vector<ll> C(N);
    rep(i,N) cin >> C[i];

    rep(i,N){
        if(K <= L[i] * C[i]){
            cout << A[i][(K - 1) % L[i]] << endl;
            return 0;
        }
        else K -= L[i] * C[i];
    }
}