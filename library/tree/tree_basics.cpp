#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 連結無向木の親・深さ・部分木サイズ・DFS前順。構築O(N)、空木も可。
// 根の親=-1。orderの逆順が子から親への木DP順になる。再帰なし。
struct TreeInfo{
    vector<int> parent;
    vector<int> depth;
    vector<int> subtree_size;
    vector<int> order;
    explicit TreeInfo(const vector<vector<int>>& tree,int root = 0){
        int N = static_cast<int>(tree.size());
        parent.assign(N,-1);
        depth.assign(N,-1);
        subtree_size.assign(N,1);
        if(N == 0) return;
        assert(0 <= root && root < N);
        vector<int> stack = {root};
        depth[root] = 0;
        while(!stack.empty()){
            int v = stack.back();
            stack.pop_back();
            order.push_back(v);
            for(int i = static_cast<int>(tree[v].size()) - 1;i >= 0;i--){
                int to = tree[v][i];
                if(depth[to] != -1) continue;
                parent[to] = v;
                depth[to] = depth[v] + 1;
                stack.push_back(to);
            }
        }
        assert(static_cast<int>(order.size()) == N);
        for(int i = N - 1;i > 0;i--){
            int v = order[i];
            subtree_size[parent[v]] += subtree_size[v];
        }
    }
};

// 連結無向木の重心を頂点番号の昇順で返す。空木は空配列、それ以外は1個か2個。
// 重心を除いた各連結成分の頂点数はN/2以下。この関数には上のTreeInfoも必要。
// 時間・空間O(N)、再帰なし。
vector<int> tree_centroids(const vector<vector<int>>& tree){
    int N = static_cast<int>(tree.size());
    TreeInfo info(tree);
    vector<int> res;
    for(int v = 0;v < N;v++){
        int largest = N - info.subtree_size[v];
        for(int to : tree[v]){
            if(to == info.parent[v]) continue;
            largest = max(largest,info.subtree_size[to]);
        }
        if(largest <= N / 2) res.push_back(v);
    }
    return res;
}

// 始点を含む頂点重みの経路和。負の重みも可、各和はlong longに収まること。
// この関数をコピーするときは上のTreeInfoも必要。O(N)。
vector<ll> tree_vertex_sums(const vector<vector<int>>& tree,const vector<ll>& weight,int root = 0){
    assert(tree.size() == weight.size());
    TreeInfo info(tree,root);
    vector<ll> sum(tree.size());
    for(int v : info.order){
        __int128 value = weight[v];
        if(info.parent[v] != -1) value += sum[info.parent[v]];
        assert(LLONG_MIN <= value && value <= LLONG_MAX);
        sum[v] = static_cast<ll>(value);
    }
    return sum;
}

struct TreeDiameter{
    int from = -1,to = -1,length = 0;
    vector<int> path;
};

// 無重み連結無向木の直径（辺数と端点間パス）。O(N)、空木は端点-1。
TreeDiameter tree_diameter(const vector<vector<int>>& tree){
    if(tree.empty()) return {};
    int from = 0;
    int to = 0;
    vector<int> dist,parent;
    // 0から最遠の頂点fromを探し、次にfromから最遠の頂点toを探す。
    for(int i = 0;i < 2;i++){
        dist.assign(tree.size(),-1);
        parent.assign(tree.size(),-1);
        queue<int> Q;
        Q.push(from);
        dist[from] = 0;
        while(!Q.empty()){
            int v = Q.front();
            Q.pop();
            for(int to : tree[v]){
                if(dist[to] != -1) continue;
                dist[to] = dist[v] + 1;
                parent[to] = v;
                Q.push(to);
            }
        }
        to = static_cast<int>(max_element(dist.begin(),dist.end()) - dist.begin());
        if(i == 0) from = to;
    }
    vector<int> path;
    for(int v = to;v != -1;v = parent[v]) path.push_back(v);
    reverse(path.begin(),path.end());
    return {from,to,dist[to],path};
}
