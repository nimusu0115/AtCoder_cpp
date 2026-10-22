#include<bits/stdc++.h>
using namespace std;

// 反復Kosaraju。成分IDは縮約DAGのトポロジカル順、0始まり。O(V+E)。
// 通常はACL scc_graphも使える。こちらは再帰の深さに依存しない。
vector<int> scc(const vector<vector<int>>& G){
    int N = static_cast<int>(G.size());
    vector<vector<int>> rG(N);
    for(int v = 0;v < N;v++){
        for(int to : G[v]) rG[to].push_back(v);
    }
    vector<bool> seen(N);
    vector<int> order,next(N),comp(N,-1);
    for(int root = 0;root < N;root++){
        if(seen[root]) continue;
        vector<int> stack = {root};
        seen[root] = true;
        while(!stack.empty()){
            int v = stack.back();
            if(next[v] == static_cast<int>(G[v].size())){
                order.push_back(v);
                stack.pop_back();
                continue;
            }
            int to = G[v][next[v]];
            next[v]++;
            if(!seen[to]){
                seen[to] = true;
                stack.push_back(to);
            }
        }
    }
    int id = 0;
    reverse(order.begin(),order.end());
    for(int root : order){
        if(comp[root] != -1) continue;
        vector<int> stack = {root};
        comp[root] = id;
        while(!stack.empty()){
            int v = stack.back();
            stack.pop_back();
            for(int to : rG[v]){
                if(comp[to] != -1) continue;
                comp[to] = id;
                stack.push_back(to);
            }
        }
        id++;
    }
    return comp;
}
