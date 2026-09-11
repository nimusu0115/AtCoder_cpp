#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
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
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
// H×W の盤面。'#' は壁、seen は到達済み、dist は始点からの距離を表す。
int H,W;
vector<vector<char>> G;
vector<vector<bool>> seen;
vector<vector<int>> dist;
void bfs_dist(set<pair<int,int>> start){
	queue<pair<int,int>> Q;
	for(auto v : start) Q.push(v);
	for(auto v : start) dist[v.first][v.second] = 0;
	while(!Q.empty()){
		int h = Q.front().first;
		int w = Q.front().second;
		Q.pop();
		rep(dir,4){
			int nh = h + dx[dir];
			int nw = w + dy[dir];

			if(nh < 0 || H <= nh || nw < 0 || W <= nw) continue;
			if(dist[nh][nw] <= dist[h][w] + 1) continue;
			if(G[nh][nw] == '#') continue;

			dist[nh][nw] = dist[h][w] + 1;
			Q.push({nh,nw});
		}
	}
}
int main() {
    int K;
    cin >> H >> W >> K;
    G.resize(H,vector<char>(W));
    rep(i,H){
        rep(j,W) cin >> G[i][j];
    }

    dist.resize(H,vector<int>(W,-1));

    vector<bool> anzenh(H,true),anzenw(W,true);
    rep(i,H) rep(j,W) if(G[i][j] == '#') anzenh[i] = false,anzenw[j] = false;
    set<pair<int,int>> anzen;
    rep(i,H) rep(j,W) if(anzenh[i] && anzenw[j]) anzen.insert({i,j});

    bfs_dist(anzen);

    int ans = 0;
    rep(i,H) rep(j,W){
        if(dist[i][j] <= K) ans++;
    }
    cout << ans << endl;
}