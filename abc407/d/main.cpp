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
ll ans = 0;
int H,W;
vector<vector<ll>> A;

void cul(vector<vector<bool>> x){
    ll res = 0;
    rep(i,H) rep(j,W) if(!x[i][j]) res ^= A[i][j];
    chmax(ans,res);
}

void solve(vector<vector<bool>> x,int n){
    if(n >= H * W) return;

    cul(x);
    int h = n / W;
    int w = n % W;
    
    solve(x,n + 1);
    if(w < W - 1 && !x[h][w] && !x[h][w + 1]){
        auto y = x;
        y[h][w] = true;
        y[h][w + 1] = true;
        solve(y,n + 1);
    }
    if(h < H - 1 && !x[h][w] && !x[h + 1][w]){
        auto y = x;
        y[h][w] = true;
        y[h + 1][w] = true;
        solve(y,n + 1);
    }
}

int main() {
    cin >> H >> W;
    A.resize(H,vector<ll>(W));
    rep(i,H) rep(j,W) cin >> A[i][j];

    vector<vector<bool>> x(H,vector<bool>(W,false));
    solve(x,0);

    cout << ans << endl;
}