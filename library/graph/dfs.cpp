#include <bits/stdc++.h>
using namespace std;

struct DFSResult {
    vector<int> parent, depth, tin, tout, preorder, postorder;
};

// 始点から到達可能な頂点を反復DFS。未到達の値=-1、根の親=-1。
// tin/toutは入出のたびに進める2N時計。O(V+E)、再帰なし。
DFSResult dfs(const vector<vector<int>>& g, int start) {
    int n = static_cast<int>(g.size());
    DFSResult r;
    r.parent.assign(n,-1); r.depth.assign(n,-1);
    r.tin.assign(n,-1); r.tout.assign(n,-1);
    if(n == 0) return r;
    assert(0 <= start && start < n);
    vector<int> next(n), stack = {start};
    int timer = 0;
    r.depth[start] = 0; r.tin[start] = timer++;
    r.preorder.push_back(start);
    while(!stack.empty()) {
        int v = stack.back();
        if(next[v] == static_cast<int>(g[v].size())) {
            r.tout[v] = timer++; r.postorder.push_back(v); stack.pop_back();
            continue;
        }
        int to = g[v][next[v]++];
        if(r.depth[to] != -1) continue;
        r.parent[to] = v; r.depth[to] = r.depth[v] + 1;
        r.tin[to] = timer++; r.preorder.push_back(to); stack.push_back(to);
    }
    return r;
}
