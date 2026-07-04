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
        cin >> N;
        string S;
        cin >> S;
        vector<ll> X(N),Y(N - 1);
        rep(i,N) cin >> X[i];
        rep(i,N - 1) cin >> Y[i];

        vector<vector<ll>> dp(N,vector<ll>(2,0));

        rep(i,N){
            if(S[i] == 'S') dp[i][1] -= X[i];
            else dp[i][0] -= X[i];

            if(i == 0) continue;
            dp[i][0] += max(dp[i - 1][0],dp[i - 1][1] + Y[i - 1]);
            dp[i][1] += max(dp[i - 1][0],dp[i - 1][1]);
        }

        cout << max(dp[N - 1][0],dp[N - 1][1]) << endl;
    }
}