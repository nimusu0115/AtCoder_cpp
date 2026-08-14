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
int H,W;
vector<string> S;
vector<vector<bool>> seen;
bool bfs_seen(pair<int,int> start){
  queue<pair<int,int>> Q;
  bool flg = false;
  Q.push(start);
  seen[start.first][start.second] = 0;
  while(!Q.empty()){
    int h = Q.front().first;
    int w = Q.front().second;
    Q.pop();
    if(h == 0 || h == H - 1 || w == 0 || w == W - 1) flg = true;
    rep(dir,4){
      int nh = h + dx[dir];
      int nw = w + dy[dir];

      if(nh < 0 || H <= nh || nw < 0 || W <= nw) continue;
      if(seen[nh][nw]) continue;
      if(S[nh][nw] == '#') continue;

      seen[nh][nw] = true;
      Q.push({nh,nw});
    }
  }
  return flg;
}

int main() {
    cin >> H >> W;
    S.resize(H);
    seen.resize(H,vector<bool>(W,false));
    rep(i,H) cin >> S[i];

    int ans = 0;
    rep(i,H){
        rep(j,W){
            if(S[i][j] == '#' || seen[i][j]) continue;
            if(!bfs_seen({i,j})) ans++;
        }
    }

    cout << ans << endl;
}