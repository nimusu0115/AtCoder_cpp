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
    vector<ll> A(N),B(N);
    rep(i,N) cin >> A[i] >> B[i];

    vector<vector<ll>> dp(N,vector<ll>(2 * K + 1,0));

    rep(i,N){
        if(i == 0){
            dp[i][0] = A[i];
            dp[i][1] = B[i];
            continue;
        }
        rep(j,2 * K + 1){
            if(j == 0){
                dp[i][j] = dp[i - 1][j] + A[i];
                continue;
            }
            /*if(dp[i - 1][j - 1] == 0) continue;
            if(dp[i - 1][j] == 0){
                if(j % 2 == 1) dp[i][j] = dp[i - 1][j - 1] + A[i];
                if(j % 2 == 0) dp[i][j] = dp[i - 1][j - 1] + B[i];
                continue;
            }*/
            if(j % 2 == 1) dp[i][j] = max(dp[i - 1][j] + B[i],dp[i - 1][j - 1] + B[i]);
            if(j % 2 == 0) dp[i][j] = max(dp[i - 1][j] + A[i],dp[i - 1][j - 1] + A[i]);
        }
    }

    ll ans = 0;
    rep(i,2 * K + 1) chmax(ans,dp[N - 1][i]);
    cout << ans << endl;
    /*rrep(j,2 * K + 1){
        rep(i,N){
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
}