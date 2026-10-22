#include <bits/stdc++.h>
using namespace std;

// 無向グラフの橋（入力辺ID）・関節点（頂点ID）。O(V+E)、再帰なし。
// 非連結・多重辺・自己ループ可。親頂点ではなく親辺IDだけを除外する。
struct Lowlink {
    vector<int> ord, low, bridges, articulation;
    Lowlink(int n, const vector<pair<int,int>>& edges) {
        assert(n >= 0);
        vector<vector<pair<int,int>>> g(n);
        for(int id = 0; id < static_cast<int>(edges.size()); ++id) {
            auto [u,v] = edges[id];
            assert(0 <= u && u < n && 0 <= v && v < n);
            g[u].push_back({v,id}); g[v].push_back({u,id});
        }
        ord.assign(n,-1); low.resize(n);
        vector<int> parent(n,-1), parent_edge(n,-1), next(n), children(n);
        vector<bool> cut(n);
        int timer = 0;
        for(int root = 0; root < n; ++root) {
            if(ord[root] != -1) continue;
            vector<int> stack = {root}; ord[root] = low[root] = timer++;
            while(!stack.empty()) {
                int v = stack.back();
                if(next[v] == static_cast<int>(g[v].size())) {
                    stack.pop_back();
                    int p = parent[v];
                    if(p == -1) cut[v] = children[v] > 1;
                    else {
                        low[p] = min(low[p],low[v]);
                        if(ord[p] < low[v]) bridges.push_back(parent_edge[v]);
                        if(parent[p] != -1 && ord[p] <= low[v]) cut[p] = true;
                    }
                    continue;
                }
                auto [to,id] = g[v][next[v]++];
                if(id == parent_edge[v]) continue;
                if(ord[to] != -1) { low[v] = min(low[v],ord[to]); continue; }
                parent[to] = v; parent_edge[to] = id; ++children[v];
                ord[to] = low[to] = timer++; stack.push_back(to);
            }
        }
        // 橋の順序はDFS帰りがけ順。ソートが必要なら呼び出し側で行う。
        for(int v = 0; v < n; ++v) if(cut[v]) articulation.push_back(v);
    }
};
