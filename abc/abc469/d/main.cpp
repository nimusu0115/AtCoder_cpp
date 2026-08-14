#include<bits/stdc++.h>
//#include <atcoder/all>
using namespace std;
//using namespace atcoder;
//using mint = modint998244353;
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
    int N,M;
    cin >> N >> M;
    vector<int> A(M),B(M);
    rep(i,M) cin >> A[i] >> B[i];
    rep(i,M) A[i]--,B[i]--;

    int a = A[0],b = B[0];
    vector<int> alpha(N,0),beta(N,0),gamma(N,0);

    rep(i,M){
        alpha[A[i]]++;
        alpha[B[i]]++;
        if(A[i] == A[0]) beta[B[i]]++;
        if(B[i] == A[0]) beta[A[i]]++;
        if(A[i] == B[0]) gamma[B[i]]++;
        if(B[i] == B[0]) gamma[A[i]]++;
    }

    int ans = 0;
    rep(i,N){
        if(alpha[A[0]] + alpha[i] - beta[i] == M && i != A[0]) ans++;
        if(alpha[B[0]] + alpha[i] - gamma[i] == M && i != B[0]) ans++;
    }
    bool flg = true;
    rep(i,M) if(A[i] != A[0] && A[i] != B[0] && B[i] != A[0] && B[i] != B[0]) flg = false;
    if(flg) ans--;
    cout << ans << endl;
}