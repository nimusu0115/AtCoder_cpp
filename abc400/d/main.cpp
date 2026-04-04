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
vector<vector<int>> dist;

void bfs_seen(pair<int,int> start,int kick){
	queue<pair<int,int>> Q;
	Q.push(start);
	if(dist[start.first][start.second] == -1) dist[start.first][start.second] = kick;
	while(!Q.empty()){
		int h = Q.front().first; 
		int w = Q.front().second;
		Q.pop();
		rep(dir,4){
			int nh = h + dx[dir];
			int nw = w + dy[dir];

			if(nh < 0 || H <= nh || nw < 0 || W <= nw) continue;
			if(dist[nh][nw] == -1 || dist[nh][nw] == kick + 1){
				dist[nh][nw] = kick + 1;
				int nnh = nh + dx[dir];
				int nnw = nw + dy[dir];
				if(nnh < 0 || H <= nnh || nnw < 0 || W <= nnw) continue;
				dist[nnh][nnw] = kick + 1;
				continue;
			}

			Q.push({nh,nw});
		}
	}
}

int main() {
    cin >> H >> W;
    S.resize(H);
    rep(i,H) cin >> S[i];

    int a,b,c,d;
    cin >> a >> b >> c >> d;

    dist.resize(H,vector<int>(W,-1));
    int kick = 0;
    while(dist[c - 1][d - 1] == -1){
        bfs_seen({a - 1,b - 1},kick);
        kick++;
    }
    cout << dist[c - 1][d - 1] << endl;
}