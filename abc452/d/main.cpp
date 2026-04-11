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
    string S,T;
    cin >> S;
    cin >> T;

    vector<vector<ll>> dp(S.size() + 1,vector<ll>(T.size() + 1,0LL));
    onerep(i,S.size()){
        onerep(j,T.size()){
            if(S[i - 1] == T[j - 1]){
                if(j == 1) dp[i][j] += dp[i - 1][j] + i;
                else if(dp[i - 1][j] >= 1) dp[i][j] += dp[i - 1][j] + 1;
                else if(dp[i - 1][j - 1] >= 1) dp[i][j] += 1;
            }
            else if(dp[i - 1][j] >= 1) dp[i][j] += dp[i - 1][j] + 1;
        }
    }

    ll ans = S.size() * (S.size() - 1) / 2 + S.size();
    ans -= dp[S.size()][T.size()];
    cout << ans << endl;

    onerep(i,S.size()){
        onerep(j,T.size()){
            cout << dp[i][j];
        }
        cout << endl;
    }
}