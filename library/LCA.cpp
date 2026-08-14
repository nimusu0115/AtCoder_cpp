#include<bits/stdc++.h>
using namespace std;

// 木上の最小共通祖先（Lowest Common Ancestor）をダブリングで求める。
// 構築は O(N log N)、各クエリは O(log N)。頂点番号は0-indexed。
struct LCA{
    int N;
    int LOG;
    vector<vector<int>> parent;
    vector<int> depth;

    // tree を根 root の根付き木として前計算する。
    LCA(const vector<vector<int>>& tree,int root = 0){
        N = static_cast<int>(tree.size());
        LOG = 1;
        while((1LL<<LOG) <= max(1,N)) LOG++;

        parent.assign(LOG,vector<int>(N,-1));
        depth.assign(N,-1);

        queue<int> Q;
        Q.push(root);
        depth[root] = 0;

        while(!Q.empty()){
            int pos = Q.front();
            Q.pop();
            for(int to : tree[pos]){
                if(to == parent[0][pos]) continue;
                if(depth[to] != -1) continue;
                parent[0][to] = pos;
                depth[to] = depth[pos] + 1;
                Q.push(to);
            }
        }

        for(int k = 0;k + 1 < LOG;k++){
            for(int v = 0;v < N;v++){
                if(parent[k][v] == -1) continue;
                parent[k + 1][v] = parent[k][parent[k][v]];
            }
        }
    }

    // 頂点 v の k 個上の祖先を返す。存在しなければ -1。
    int ancestor(int v,int k) const{
        for(int i = 0;i < LOG && v != -1;i++){
            if((k>>i) & 1) v = parent[i][v];
        }
        return v;
    }

    // 頂点 u と v の最小共通祖先を返す。
    int query(int u,int v) const{
        if(depth[u] < depth[v]) swap(u,v);
        u = ancestor(u,depth[u] - depth[v]);
        if(u == v) return u;

        for(int k = LOG - 1;k >= 0;k--){
            if(parent[k][u] != parent[k][v]){
                u = parent[k][u];
                v = parent[k][v];
            }
        }
        return parent[0][u];
    }

    // u から v までの辺の本数を返す。
    int distance(int u,int v) const{
        int p = query(u,v);
        return depth[u] + depth[v] - 2 * depth[p];
    }
};
