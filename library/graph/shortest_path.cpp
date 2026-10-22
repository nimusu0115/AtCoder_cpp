#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// G[v] = {行き先, 非負long long重み}。到達不能/表現範囲外=LLONG_MAX。
// 有限距離はLLONG_MAX未満。加算前に範囲を確認する。O((V+E)log(E+2))。
vector<ll> dijkstra(const vector<vector<pair<int,ll>>>& G,int start){
    const ll llinf = numeric_limits<ll>::max();
    vector<ll> dist(G.size(),llinf);
    if(G.empty()) return dist;
    assert(0 <= start && start < static_cast<int>(G.size()));
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;
    dist[start] = 0;
    Q.push({0,start});
    while(!Q.empty()){
        ll distance = Q.top().first;
        int pos = Q.top().second;
        Q.pop();
        if(distance != dist[pos]) continue;
        for(auto edge : G[pos]){
            int to = edge.first;
            ll cost = edge.second;
            assert(cost >= 0);
            if(cost >= llinf - distance || distance + cost >= dist[to]) continue;
            dist[to] = distance + cost;
            Q.push({dist[to],to});
        }
    }
    return dist;
}

// 辺重み0/1専用。到達不能=-1。確定済み頂点は再展開せずO(V+E)。
vector<int> zero_one_bfs(const vector<vector<pair<int,int>>>& G,int start){
    vector<int> dist(G.size(),-1);
    if(G.empty()) return dist;
    assert(0 <= start && start < static_cast<int>(G.size()));
    vector<bool> kakutei(G.size());
    deque<int> Q;
    dist[start] = 0;
    Q.push_front(start);
    while(!Q.empty()){
        int pos = Q.front();
        Q.pop_front();
        if(kakutei[pos]) continue;
        kakutei[pos] = true;
        for(auto edge : G[pos]){
            int to = edge.first;
            int cost = edge.second;
            assert(cost == 0 || cost == 1);
            if(dist[to] != -1 && dist[to] <= dist[pos] + cost) continue;
            dist[to] = dist[pos] + cost;
            if(cost == 0) Q.push_front(to);
            else Q.push_back(to);
        }
    }
    return dist;
}
