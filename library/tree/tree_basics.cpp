#include <bits/stdc++.h>
using namespace std;

// 連結無向木の親・深さ・部分木サイズ・DFS前順。構築O(N)、空木も可。
// 根の親=-1。orderの逆順が子から親への木DP順になる。再帰なし。
struct TreeInfo {
    vector<int> parent, depth, subtree_size, order;
    explicit TreeInfo(const vector<vector<int>>& tree, int root = 0) {
        int n = static_cast<int>(tree.size());
        parent.assign(n,-1); depth.assign(n,-1); subtree_size.assign(n,1);
        if(n == 0) return;
        assert(0 <= root && root < n);
        vector<int> stack = {root}; depth[root] = 0;
        while(!stack.empty()) {
            int v = stack.back(); stack.pop_back(); order.push_back(v);
            for(auto it = tree[v].rbegin(); it != tree[v].rend(); ++it) {
                int to = *it;
                if(depth[to] != -1) continue;
                parent[to] = v; depth[to] = depth[v]+1; stack.push_back(to);
            }
        }
        assert(static_cast<int>(order.size()) == n);
        for(int i = n-1; i > 0; --i) {
            int v = order[i]; subtree_size[parent[v]] += subtree_size[v];
        }
    }
};

// 始点を含む頂点重みの経路和。負の重みも可、各和はlong longに収まること。
// この関数をコピーするときは上のTreeInfoも必要。O(N)。
vector<long long> tree_vertex_sums(const vector<vector<int>>& tree, const vector<long long>& weight, int root = 0) {
    assert(tree.size() == weight.size());
    TreeInfo info(tree,root);
    vector<long long> sum(tree.size());
    for(int v : info.order) {
        __int128 value = weight[v];
        if(info.parent[v] != -1) value += sum[info.parent[v]];
        assert(LLONG_MIN <= value && value <= LLONG_MAX);
        sum[v] = static_cast<long long>(value);
    }
    return sum;
}

struct TreeDiameter {
    int from = -1, to = -1, length = 0;
    vector<int> path;
};

// 無重み連結無向木の直径（辺数と端点間パス）。O(N)、空木は端点-1。
TreeDiameter tree_diameter(const vector<vector<int>>& tree) {
    if(tree.empty()) return {};
    auto distances = [&](int start) {
        vector<int> dist(tree.size(),-1), parent(tree.size(),-1);
        queue<int> q; q.push(start); dist[start] = 0;
        while(!q.empty()) {
            int v = q.front(); q.pop();
            for(int to : tree[v]) if(dist[to] == -1) {
                dist[to] = dist[v]+1; parent[to] = v; q.push(to);
            }
        }
        return make_pair(dist,parent);
    };
    auto first = distances(0).first;
    int from = static_cast<int>(max_element(first.begin(),first.end())-first.begin());
    auto [dist,parent] = distances(from);
    int to = static_cast<int>(max_element(dist.begin(),dist.end())-dist.begin());
    vector<int> path;
    for(int v = to; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(),path.end());
    return {from,to,dist[to],path};
}
