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
    string S;
    cin >> S;
    int N = S.size();

    vector<vector<ll>> dp(N + 1,vector<ll>(3,0));
    onerep(i,N){
        int c = S[i - 1] - 'a';
        rep(j,3){
            if(j != c) dp[i][j] = dp[i - 1][j];
            else{
                rep(k,3){
                    if(k != j) dp[i][j] += dp[i - 1][k];
                    else dp[i][j] += dp[i - 1][j] + 1;
                }
                dp[i][j] %= 998244353;
            }
        }
    }

    ll ans = 0;
    rep(i,3) ans = (ans + dp[N][i]) % 998244353;
    cout << ans << endl;
}