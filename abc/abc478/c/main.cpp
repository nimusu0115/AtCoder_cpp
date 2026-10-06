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

int main() {
    ll N,K;
    cin >> N >> K;
    vector<ll> A(N),B(K);
    rep(i,N) cin >> A[i];

    rep(i,N){
        if(i == 0) continue;
        if(A[i - 1] <= A[i]) continue;
        ll m = min(i - 1,int(N - K));
        rep(j,K) B[j] = A[m + j];
        sort(ALL(B));
        rep(j,K) A[m + j] = B[j];
        break;
    }

    bool flg = true;
    rep(i,N){
        if(i == 0) continue;
        if(A[i - 1] > A[i]) flg = false;
    }

    if(flg) cout << "Yes" << endl;
    else cout << "No" << endl;
    //rep(i,N) cout << A[i] << endl;
}