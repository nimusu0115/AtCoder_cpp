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
    ll N,K;
    cin >> N >> K;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];

    int ans = 0;
    ll k = 0;
    rep(i,N){
        bool flg = true;
        rep(j,62) if(((K>>j) & 1) < ((A[i]>>j) & 1)) flg = false;
        if(flg){
            k = k | A[i];
            ans++;
        }
    }
    if(k == K && ans != 0) cout << ans << endl;
    else cout << -1 << endl;
}