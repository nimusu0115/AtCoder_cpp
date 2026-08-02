#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i = 0;i < n;i++)
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int H,W;
vector<vector<char>> G;
vector<vector<bool>> seen;
vector<vector<int>> dist;
//到達可能性（グリッド）
void bfs_seen(pair<int,int> start){
	queue<pair<int,int>> Q;
	Q.push(start);
	dist[start.first][start.second] = 0;
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
			Q.push({nh,nw});
		}
	}
}

//最短距離（グリッド）
void bfs_dist(pair<int,int> start){
	queue<pair<int,int>> Q;
	Q.push(start);
	dist[start.first][start.second] = 0;
	while(!Q.empty()){
		int h = Q.front().first;
		int w = Q.front().second;
		Q.pop();
		rep(dir,4){
			int nh = h + dx[dir];
			int nw = w + dy[dir];

			if(dist[nh][nw] != -1) continue;
			if(nh < 0 || H <= nh || nw < 0 || W <= nw) continue;
			if(G[nh][nw] == '#') continue;

			dist[nh][nw] = dist[h][w] + 1;
			Q.push({nh,nw});
		}
	}
}