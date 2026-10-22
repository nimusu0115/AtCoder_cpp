#include<bits/stdc++.h>
using namespace std;

struct DFSResult{
    vector<int> parent;
    vector<int> depth;
    vector<int> tin,tout;
    vector<int> preorder,postorder;
};

// 始点から到達可能な頂点を反復DFS。未到達の値=-1、根の親=-1。
// tin/toutは入出のたびに進める2N時計。O(V+E)、再帰なし。
DFSResult dfs(const vector<vector<int>>& G,int start){
    int N = static_cast<int>(G.size());
    DFSResult res;
    res.parent.assign(N,-1);
    res.depth.assign(N,-1);
    res.tin.assign(N,-1);
    res.tout.assign(N,-1);
    if(N == 0) return res;
    assert(0 <= start && start < N);
    vector<int> next(N),stack = {start};
    int timer = 0;
    res.depth[start] = 0;
    res.tin[start] = timer++;
    res.preorder.push_back(start);
    while(!stack.empty()){
        int pos = stack.back();
        if(next[pos] == static_cast<int>(G[pos].size())){
            res.tout[pos] = timer++;
            res.postorder.push_back(pos);
            stack.pop_back();
            continue;
        }
        int to = G[pos][next[pos]];
        next[pos]++;
        if(res.depth[to] != -1) continue;
        res.parent[to] = pos;
        res.depth[to] = res.depth[pos] + 1;
        res.tin[to] = timer++;
        res.preorder.push_back(to);
        stack.push_back(to);
    }
    return res;
}
