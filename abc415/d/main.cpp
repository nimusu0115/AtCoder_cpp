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
    ll N,M;
    cin >> N >> M;
    vector<ll> A(M),B(M);
    rep(i,M) cin >> A[i] >> B[i];
    vector<pair<ll,ll>> AB(M);
    rep(i,M) AB[i] = {A[i] - B[i],i};
    sort(ALL(AB));
    vector<int> ABinverse(M);
    rep(i,M) ABinverse[AB[i].second] = i;
    auto Acp = A,Bcp = B;
    rep(i,M){
        A[ABinverse[i]] = Acp[i];
        B[ABinverse[i]] = Bcp[i];
    }
    
    ll ans = 0;
    rep(i,M){
        if(A[i] > N) continue;
        ll exchange = (N - B[i]) / (A[i] - B[i]);
        ans += exchange;
        N -= exchange * (A[i] - B[i]);
    }
    cout << ans << endl;
}