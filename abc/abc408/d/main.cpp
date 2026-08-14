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
    int T;
    cin >> T;

    while(T > 0){
        T--;

        int N;
        string S;
        cin >> N;
        cin >> S;

        vector<vector<int>> dp(N,vector<int>(3,inf));

        rep(i,N){
            if(i == 0){
                if(S[i] == '0'){
                    dp[i][0] = 0;
                    dp[i][1] = 1;
                }
                if(S[i] == '1'){
                    dp[i][0] = 1;
                    dp[i][1] = 0;
                }
                continue;
            }
            if(S[i] == '0'){
                dp[i][0] = dp[i - 1][0];
                dp[i][1] = min(dp[i - 1][0],dp[i - 1][1]) + 1;
                dp[i][2] = min(dp[i - 1][1],dp[i - 1][2]);
            }
            if(S[i] == '1'){
                dp[i][0] = dp[i - 1][0] + 1;
                dp[i][1] = min(dp[i - 1][0],dp[i - 1][1]);
                dp[i][2] = min(dp[i - 1][1],dp[i - 1][2]) + 1;
            }
        }
        int ans = inf;
        rep(i,3) chmin(ans,dp[N - 1][i]);
        cout << ans << endl;
    }
}