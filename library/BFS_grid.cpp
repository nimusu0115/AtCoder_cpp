#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i = 0;i < n;i++)
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
// H×W の盤面。'#' は壁、seen は到達済み、dist は始点からの距離を表す。
int H,W;
vector<vector<char>> G;
vector<vector<bool>> seen;
vector<vector<int>> dist;

// start から壁を避けて4方向に移動し、到達できるマスを seen=true にする。
// 前提: seen は H×W の false で初期化され、start は盤面内の通行可能なマスである。
void bfs_seen(pair<int,int> start){
	queue<pair<int,int>> Q;
	Q.push(start);
	seen[start.first][start.second] = true;
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

// start から各マスへの最短移動回数を dist に記録する。
// 到達不能なマスは -1 のまま残る。前提: dist は H×W の -1 で初期化されている。
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

			if(nh < 0 || H <= nh || nw < 0 || W <= nw) continue;
			if(dist[nh][nw] != -1) continue;
			if(G[nh][nw] == '#') continue;

			dist[nh][nw] = dist[h][w] + 1;
			Q.push({nh,nw});
		}
	}
}
