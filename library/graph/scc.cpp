#include <bits/stdc++.h>
using namespace std;

// 反復Kosaraju。成分IDは縮約DAGのトポロジカル順、0始まり。O(V+E)。
// 通常はACL scc_graphも使える。こちらは再帰の深さに依存しない。
vector<int> scc(const vector<vector<int>>& g) {
    int n = static_cast<int>(g.size());
    vector<vector<int>> reverse_graph(n);
    for(int v = 0; v < n; ++v) for(int to : g[v]) reverse_graph[to].push_back(v);
    vector<bool> seen(n);
    vector<int> order, next(n), component(n,-1);
    for(int root = 0; root < n; ++root) {
        if(seen[root]) continue;
        vector<int> stack = {root}; seen[root] = true;
        while(!stack.empty()) {
            int v = stack.back();
            if(next[v] == static_cast<int>(g[v].size())) {
                order.push_back(v); stack.pop_back(); continue;
            }
            int to = g[v][next[v]++];
            if(!seen[to]) { seen[to] = true; stack.push_back(to); }
        }
    }
    int id = 0;
    reverse(order.begin(),order.end());
    for(int root : order) {
        if(component[root] != -1) continue;
        vector<int> stack = {root}; component[root] = id;
        while(!stack.empty()) {
            int v = stack.back(); stack.pop_back();
            for(int to : reverse_graph[v]) if(component[to] == -1) {
                component[to] = id; stack.push_back(to);
            }
        }
        ++id;
    }
    return component;
}
