#include<bits/stdc++.h>
using namespace std;
#define ll long long
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}
vector<vector<int>> G;
vector<bool> seen;
vector<ll> dist;
vector<bool> kakutei;
//到達可能性
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

//距離計算
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

//距離計算（重み付き）（自己価値含む）
void bfs_dist(int start,vector<ll> V){
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

//ダイクストラ法
void dijkstra(int start,const vector<vector<pair<int,ll>>>& G){
  priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;
  Q.push({0,start});
  dist[start] = 0;
  kakutei[start] = 0;
  while(!Q.empty()){
    int pos = Q.top().second;
    Q.pop();
    if(kakutei[pos]) continue;
    kakutei[pos] = true;
    for(auto v : G[pos]){
        int to = v.first;
        ll cost = v.second;
        if(dist[to] <= dist[pos] + cost) continue;
        chmin(dist[to],dist[pos] + cost);
        Q.push({dist[to],to});
        }
    }
}