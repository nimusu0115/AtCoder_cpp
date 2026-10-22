#include<bits/stdc++.h>
using namespace std;

// 頂点をDFS前順に一度ずつ並べるEuler Tour。構築O(N)、再帰なし。
// 部分木=[tin[v],tout[v])。LCA用の2N-1回の歩行列ではない。
struct EulerTour{
    vector<int> tin,tout,order;
    explicit EulerTour(const vector<vector<int>>& tree,int root = 0){
        int N = static_cast<int>(tree.size());
        tin.assign(N,-1);
        tout.assign(N,-1);
        if(N == 0) return;
        assert(0 <= root && root < N);
        vector<int> next(N),stack = {root};
        tin[root] = 0;
        order.push_back(root);
        while(!stack.empty()){
            int v = stack.back();
            if(next[v] == static_cast<int>(tree[v].size())){
                tout[v] = static_cast<int>(order.size());
                stack.pop_back();
                continue;
            }
            int to = tree[v][next[v]];
            next[v]++;
            if(tin[to] != -1) continue;
            tin[to] = static_cast<int>(order.size());
            order.push_back(to);
            stack.push_back(to);
        }
        assert(static_cast<int>(order.size()) == N);
    }
    bool is_ancestor(int u,int v) const{
        return tin[u] <= tin[v] && tin[v] < tout[u];
    }
};
