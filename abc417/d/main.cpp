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
    int N;
    cin >> N;
    vector<int> P(N),A(N),B(N);
    rep(i,N) cin >> P[i] >> A[i] >> B[i];

    vector<vector<ll>> dp(N,vector<ll>(1010,0));
    rrep(i,N){
        rep(j,1010){
            if(i == N - 1){
                if(j <= P[i]) dp[i][j] = j + A[i];
                else dp[i][j] = max(0,j - B[i]);
                continue;
            }
            if(j <= P[i]) dp[i][j] = dp[i + 1][j + A[i]];
            else dp[i][j] = dp[i + 1][max(0,j - B[i])];
        }
    }

    vector<ll> BB(N,0);
    rep(i,N){
        if(i == 0) BB[i] = B[i];
        else BB[i] = BB[i - 1] + B[i];
    }

    int Q;
    cin >> Q;
    while(Q > 0){
        Q--;

        ll X;
        cin >> X;

        if(X - BB[N - 2] > 1009){
            cout << X - BB[N - 1] << endl;
        }
        else if(X < 1010) cout << dp[0][X] << endl;
        else{
            auto itr = lower_bound(ALL(BB),X - 1009);
            int k = distance(BB.begin(),itr);
            cout << dp[k + 1][X - *itr] << endl;
        }
    }
}