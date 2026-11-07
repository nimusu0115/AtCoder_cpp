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
    int N,H,M;
    cin >> N >> H >> M;
    vector<int> A(N),B(N);
    rep(i,N) cin >> A[i] >> B[i];

    vector<vector<int>> dp(N + 1,vector<int>(3010,-1));

    dp[0][H] = M;

    rep(i,N){
        rep(h,3010){
            if(h >= A[i]) chmax(dp[i + 1][h - A[i]],dp[i][h]);
            if(dp[i][h] >= B[i]) chmax(dp[i + 1][h],dp[i][h] - B[i]);
        }
    }

    int ans = 0;
    onerep(i,N){
        bool flg = false;
        rep(h,3010) if(dp[i][h] >= 0) flg = true;
        if(flg) ans = i;
    }

    cout << ans << endl;
}