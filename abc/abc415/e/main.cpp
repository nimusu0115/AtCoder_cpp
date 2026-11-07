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

vector<vector<ll>> memo;

ll dp(vector<vector<ll>> &A,vector<ll> &P,ll h,ll w){
    int H = A.size();
    int W = A[0].size();

    if(h == H - 1 && w == W - 1) return max(0LL,P[h + w] - A[h][w]);
    if(memo[h][w] != llinf) return memo[h][w];

    if(h == H - 1) return memo[h][w] = max(0LL,dp(A,P,h,w + 1) + P[h + w] - A[h][w]);
    else if(w == W - 1) return memo[h][w] = max(0LL,dp(A,P,h + 1,w) + P[h + w] - A[h][w]);
    else return memo[h][w] = max(0LL,min(dp(A,P,h,w + 1) + P[h + w] - A[h][w],dp(A,P,h + 1,w) + P[h + w] - A[h][w]));
}

int main() {
    int H,W;
    cin >> H >> W;
    memo.resize(H,vector<ll>(W,llinf));
    vector<vector<ll>> A(H,vector<ll>(W));
    rep(i,H){
        rep(j,W){
            cin >> A[i][j];
        }
    }
    vector<ll> P(H + W - 1);
    rep(i,H + W - 1) cin >> P[i];

    cout << dp(A,P,0,0) << endl;
}