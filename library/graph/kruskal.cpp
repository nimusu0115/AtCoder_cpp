#include<bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;
using ll = long long;

struct KruskalEdge{
    int from,to;
    ll cost;
};
struct KruskalResult{
    ll cost;
    vector<int> edge_ids; // 入力配列の添字
    int components;
    bool connected() const{
        return components <= 1;
    }
};

// 無向グラフの最小全域森。負辺・多重辺・自己ループ可。O(V+E log(E+1))。
// 非連結ならcomponents>1、n=0は空の森。合計費用はlong longに収まること。
KruskalResult kruskal(int N,const vector<KruskalEdge>& edges){
    assert(N >= 0);
    vector<int> ids(edges.size());
    iota(ids.begin(),ids.end(),0);
    sort(ids.begin(),ids.end(),[&](int a,int b){
        if(edges[a].cost != edges[b].cost) return edges[a].cost < edges[b].cost;
        return a < b;
    });
    atcoder::dsu uf(N);
    KruskalResult res{0,{},N};
    __int128 total = 0;
    for(int id : ids){
        int u = edges[id].from;
        int v = edges[id].to;
        ll cost = edges[id].cost;
        assert(0 <= u && u < N && 0 <= v && v < N);
        if(uf.same(u,v)) continue;
        uf.merge(u,v);
        res.components--;
        total += cost;
        res.edge_ids.push_back(id);
    }
    assert(LLONG_MIN <= total && total <= LLONG_MAX);
    res.cost = static_cast<ll>(total);
    return res;
}
