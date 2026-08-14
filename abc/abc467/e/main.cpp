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
    ll N,M;
    cin >> N >> M;
    vector<ll> A(N),B(N - 1);
    rep(i,N) cin >> A[i];
    rep(i,N - 1) cin >> B[i];

    vector<ll> a(N - 1);
    rep(i,N - 1) a[i] = (A[i] + A[i + 1]) % M;

    ll n = N - 1;
    vector<ll> l(n),r(n);
    rep(i,n){
        
    }
}