#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int main() {
    int N,K;
    cin >> N >> K;
    vector<ll> A(N),B(N),C(N);
    rep(i,N) cin >> A[i] >> B[i];
    rep(i,N) C[i] = A[i] - B[i];
    sort(ALL(C));
    reverse(ALL(C));
    ll waribiki = 0,ans = 0;
    rep(i,K) waribiki += C[i];
    rep(i,N) ans += A[i];
    ans = ans - waribiki;
    cout << ans << endl;
}