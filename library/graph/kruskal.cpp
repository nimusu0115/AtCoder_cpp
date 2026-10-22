#include <bits/stdc++.h>
#include <atcoder/dsu>
using namespace std;

struct KruskalEdge { int from, to; long long cost; };
struct KruskalResult {
    long long cost;
    vector<int> edge_ids; // 入力配列の添字
    int components;
    bool connected() const { return components <= 1; }
};

// 無向グラフの最小全域森。負辺・多重辺・自己ループ可。O(V+E log(E+1))。
// 非連結ならcomponents>1、n=0は空の森。合計費用はlong longに収まること。
KruskalResult kruskal(int n, const vector<KruskalEdge>& edges) {
    assert(n >= 0);
    vector<int> ids(edges.size()); iota(ids.begin(),ids.end(),0);
    sort(ids.begin(),ids.end(),[&](int a,int b) {
        return edges[a].cost != edges[b].cost ? edges[a].cost < edges[b].cost : a < b;
    });
    atcoder::dsu uf(n);
    KruskalResult result{0,{},n};
    __int128 total = 0;
    for(int id : ids) {
        auto [u,v,cost] = edges[id];
        assert(0 <= u && u < n && 0 <= v && v < n);
        if(uf.same(u,v)) continue;
        uf.merge(u,v); --result.components; total += cost; result.edge_ids.push_back(id);
    }
    assert(LLONG_MIN <= total && total <= LLONG_MAX);
    result.cost = static_cast<long long>(total);
    return result;
}
