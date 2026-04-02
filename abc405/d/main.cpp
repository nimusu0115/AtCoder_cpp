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
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const char arrow[4] = {'^','<','v','>'};
int H,W;
vector<vector<char>> G;
vector<vector<bool>> seen;
queue<pair<int,int>> Q;
vector<vector<char>> ans;
//到達可能性（グリッド）
void bfs_seen(){
  while(!Q.empty()){
    int h = Q.front().first;
    int w = Q.front().second;
    Q.pop();
    rep(dir,4){
      int nh = h + dx[dir];
      int nw = w + dy[dir];

      if(nh < 0 || H <= nh || nw < 0 || W <= nw) continue;
      if(seen[nh][nw]) continue;
      if(G[nh][nw] == '#') continue;

      seen[nh][nw] = true;
      ans[nh][nw] = arrow[dir];
      Q.push({nh,nw});
    }
  }
}

int main() {
    cin >> H >> W;
    G.resize(H,vector<char>(W));
    ans.resize(H,vector<char>(W));
    vector<pair<int,int>> escape;
    rep(i,H) rep(j,W){
        cin >> G[i][j];
        if(G[i][j] == 'E') escape.push_back({i,j});
        if(G[i][j] != '.') ans[i][j] = G[i][j];
    }
    seen.resize(H,vector<bool>(W,false));
    for(auto v : escape){
        Q.push(v);
        seen[v.first][v.second] = true;
    }
    bfs_seen();

    rep(i,H){
        rep(j,W) cout << ans[i][j];
        cout << endl;
    }
}