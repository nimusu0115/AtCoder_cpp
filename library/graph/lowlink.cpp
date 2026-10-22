#include<bits/stdc++.h>
using namespace std;

// 無向グラフの橋（入力辺ID）・関節点（頂点ID）。O(V+E)、再帰なし。
// 非連結・多重辺・自己ループ可。親頂点ではなく親辺IDだけを除外する。
struct Lowlink{
    vector<int> ord,low,bridges,articulation;
    Lowlink(int N,const vector<pair<int,int>>& edges){
        assert(N >= 0);
        vector<vector<pair<int,int>>> G(N);
        for(int id = 0;id < static_cast<int>(edges.size());id++){
            int u = edges[id].first;
            int v = edges[id].second;
            assert(0 <= u && u < N && 0 <= v && v < N);
            G[u].push_back({v,id});
            G[v].push_back({u,id});
        }
        ord.assign(N,-1);
        low.resize(N);
        vector<int> parent(N,-1),parent_edge(N,-1),next(N),children(N);
        vector<bool> cut(N);
        int timer = 0;
        for(int root = 0;root < N;root++){
            if(ord[root] != -1) continue;
            vector<int> stack = {root};
            ord[root] = low[root] = timer++;
            while(!stack.empty()){
                int v = stack.back();
                if(next[v] == static_cast<int>(G[v].size())){
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
                int to = G[v][next[v]].first;
                int id = G[v][next[v]].second;
                next[v]++;
                if(id == parent_edge[v]) continue;
                if(ord[to] != -1){
                    low[v] = min(low[v],ord[to]);
                    continue;
                }
                parent[to] = v;
                parent_edge[to] = id;
                children[v]++;
                ord[to] = low[to] = timer++;
                stack.push_back(to);
            }
        }
        // 橋の順序はDFS帰りがけ順。ソートが必要なら呼び出し側で行う。
        for(int v = 0;v < N;v++) if(cut[v]) articulation.push_back(v);
    }
};
