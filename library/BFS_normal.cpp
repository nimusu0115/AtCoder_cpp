#include<bits/stdc++.h>
using namespace std;
#define ll long long
// a を現在値と b の大きい方／小さい方に更新する。
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

// 無重みグラフと、各探索で使用する状態配列。
vector<vector<int>> G;
vector<bool> seen;
vector<ll> dist;
vector<bool> kakutei;

// 無重みグラフ上で start から到達できる頂点を seen=true にする。
// 前提: seen は頂点数と同じサイズの false で初期化されている。
void bfs_seen(int start){
	queue<int> Q;
	Q.push(start);
	seen[start] = true;
	while(!Q.empty()){
		int pos = Q.front();
		Q.pop();
		for(int to : G[pos]){
			if(seen[to] == false){
				seen[to] = true;
				Q.push(to);
			}
		}
	}
}

// 無重みグラフ上で start から各頂点への最短辺数を dist に記録する。
// 到達不能な頂点は -1 のまま残る。前提: dist は -1 で初期化されている。
void bfs_dist(int start){
	queue<int> Q;
	Q.push(start);
	dist[start] = 0;
	while(!Q.empty()){
		int pos = Q.front();
		Q.pop();
		for(int to : G[pos]){
			if(dist[to] == -1){
				dist[to] = dist[pos] + 1;
				Q.push(to);
			}
		}
	}
}

// start から各頂点までの頂点重み V の累積和を dist に記録する。
// 木など、start から各頂点への経路が一意なグラフで使用する。
// 始点の重み V[start] も累積和に含む。前提: dist は -1 で初期化されている。
void bfs_dist(int start,const vector<ll>& V){
	queue<int> Q;
	Q.push(start);
	dist[start] = V[start];
	while(!Q.empty()){
		int pos = Q.front();
		Q.pop();
		for(int to : G[pos]){
			if(dist[to] == -1){
				dist[to] = dist[pos] + V[to];
				Q.push(to);
			}
		}
	}
}

// 非負の辺重みを持つグラフで、start から各頂点への最短距離を dist に記録する。
// weighted_graph[v] の各要素は {行き先, 辺の重み}。到達不能なら LLONG_MAX のまま残る。
void dijkstra(int start,const vector<vector<pair<int,ll>>>& weighted_graph){
	dist.assign(weighted_graph.size(), numeric_limits<ll>::max());
	kakutei.assign(weighted_graph.size(), false);
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;
	Q.push({0,start});
	dist[start] = 0;
	while(!Q.empty()){
		int pos = Q.top().second;
		Q.pop();
		if(kakutei[pos]) continue;
		kakutei[pos] = true;
		for(auto v : weighted_graph[pos]){
			int to = v.first;
			ll cost = v.second;
			if(dist[to] <= dist[pos] + cost) continue;
			chmin(dist[to],dist[pos] + cost);
			Q.push({dist[to],to});
        }
    }
}
