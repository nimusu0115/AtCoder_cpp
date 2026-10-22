#include <bits/stdc++.h>
using namespace std;

// g[v] = {行き先, 非負long long重み}。到達不能/表現範囲外=LLONG_MAX。
// 有限距離はLLONG_MAX未満。加算前に範囲を確認する。O((V+E)log(E+2))。
vector<long long> dijkstra(const vector<vector<pair<int,long long>>>& g, int start) {
    const auto infinity = numeric_limits<long long>::max();
    vector<long long> dist(g.size(), infinity);
    if(g.empty()) return dist;
    assert(0 <= start && start < static_cast<int>(g.size()));
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<pair<long long,int>>> q;
    dist[start] = 0; q.push({0,start});
    while(!q.empty()) {
        auto [d,v] = q.top(); q.pop();
        if(d != dist[v]) continue;
        for(auto [to,w] : g[v]) {
            assert(w >= 0);
            if(w >= infinity - d || d + w >= dist[to]) continue;
            dist[to] = d + w; q.push({dist[to],to});
        }
    }
    return dist;
}

// 辺重み0/1専用。到達不能=-1。確定済み頂点は再展開せずO(V+E)。
vector<int> zero_one_bfs(const vector<vector<pair<int,int>>>& g, int start) {
    vector<int> dist(g.size(), -1);
    if(g.empty()) return dist;
    assert(0 <= start && start < static_cast<int>(g.size()));
    vector<bool> done(g.size());
    deque<int> q;
    dist[start] = 0; q.push_front(start);
    while(!q.empty()) {
        int v = q.front(); q.pop_front();
        if(done[v]) continue;
        done[v] = true;
        for(auto [to,w] : g[v]) {
            assert(w == 0 || w == 1);
            if(dist[to] != -1 && dist[to] <= dist[v] + w) continue;
            dist[to] = dist[v] + w;
            if(w == 0) q.push_front(to); else q.push_back(to);
        }
    }
    return dist;
}
