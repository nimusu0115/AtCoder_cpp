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
int N;
vector<int> dp;
vector<int> deg;
vector<vector<int>> G;

int rec(int v){
    if(dp[v] != -1) return dp[v];
    if(deg[v] < 3) return 0;

    int res = 1;
    for(auto to : G[v]){
        if(deg[to] < 3) continue;
        if(deg[to] == 3) chmax(res,2);
        if(deg[to] >= 4) chmax(res,rec(to) + 1);
    }
    return dp[v] = res;
}

int solve(void){
    int ans = 0;
    rep(i,N) chmax(ans,rec(i));
    return ans;
}

int main() {
    ll Q;
    cin >> Q;
    while(Q > 0){
        Q--;

        cin >> N;
        G.resize(N,vector<int>{});
        deg.resize(N,0);
        dp.resize(N,-1);
        rep(i,N - 1){
            int a,b;
            cin >> a >> b;
            G[a - 1].push_back(b - 1);
            G[b - 1].push_back(a - 1);
            deg[a - 1]++;
            deg[b - 1]++;
        }
        cout << solve() << endl;
    }
}