#include "../tree/tree_basics.cpp"
#include "../tree/lca.cpp"
#include "../tree/euler_tour.cpp"
#include "../tree/hld.cpp"
#include "../tree/rerooting.cpp"
#include "../graph/dfs.cpp"

mt19937 rng(20261022);
using ll = long long;
using Graph = vector<vector<int>>;
Graph make_tree(int n, int shape) {
    Graph g(n);
    for(int v = 1; v < n; ++v) {
        int p = shape == 0 ? v-1 : shape == 1 ? 0 : static_cast<int>(rng()%v);
        g[v].push_back(p); g[p].push_back(v);
    }
    for(auto& row : g) shuffle(row.begin(),row.end(),rng);
    return g;
}

void small_tree(const Graph& g, int root) {
    int n = static_cast<int>(g.size());
    // 各頂点を削除して連結成分を数える愚直解と比較。
    vector<int> expected_centroids;
    for(int removed = 0; removed < n; removed++) {
        vector<bool> seen(n,false);
        seen[removed] = true;
        int largest = 0;
        for(int start = 0; start < n; start++) {
            if(seen[start]) continue;
            queue<int> q;
            q.push(start);
            seen[start] = true;
            int size = 0;
            while(!q.empty()) {
                int v = q.front(); q.pop();
                size++;
                for(int to : g[v]) {
                    if(seen[to]) continue;
                    seen[to] = true;
                    q.push(to);
                }
            }
            largest = max(largest,size);
        }
        if(largest <= n / 2) expected_centroids.push_back(removed);
    }
    assert(tree_centroids(g) == expected_centroids);
    TreeInfo info(g,root); LCA lca(g,root); EulerTour et(g,root); HLD hld(g,root);
    auto traversal = dfs(g,root);
    assert(info.parent == lca.parent[0] && info.parent == traversal.parent && hld.parent == info.parent);
    assert(info.depth == lca.depth && info.depth == traversal.depth && hld.depth == info.depth);
    assert(et.order == info.order && et.order == traversal.preorder);
    vector<ll> weight(n); for(int i = 0; i < n; ++i) weight[i] = i%7-3;
    auto sums = tree_vertex_sums(g,weight,root);
    vector<vector<pair<int,int>>> edges(n);
    vector<ll> edge_weight;
    for(int v = 0; v < n; ++v) for(int to : g[v]) if(v < to) {
        int id = static_cast<int>(edge_weight.size()); edge_weight.push_back((v+to)%11);
        edges[v].push_back({to,id}); edges[to].push_back({v,id});
    }
    // 全方位木DP: {根からの距離和, 頂点数}。各根からの愚直探索と比較。
    using State = pair<ll,ll>;
    auto result = rerooting(edges,State{0,0},
        [](State a, State b) { return State{a.first+b.first,a.second+b.second}; },
        [](State a, int) { return State{a.first,a.second+1}; },
        [&](State a, int, int, int id) { return State{a.first+a.second*edge_weight[id],a.second}; },root);
    int diameter = 0;
    for(int u = 0; u < n; ++u) {
        vector<int> parent(n,-1), depth(n,-1); vector<ll> distance(n); queue<int> q;
        q.push(u); depth[u] = 0;
        while(!q.empty()) {
            int v=q.front(); q.pop();
            for(auto [to,id] : edges[v]) if(depth[to] == -1) {
                parent[to]=v; depth[to]=depth[v]+1; distance[to]=distance[v]+edge_weight[id]; q.push(to);
            }
        }
        assert(result[u] == State(accumulate(distance.begin(),distance.end(),0LL),n));
        ll expected_sum=0;
        for(int v=u; v!=-1; v=info.parent[v]) expected_sum += weight[v];
        assert(sums[u] == expected_sum);
        int size=0;
        for(int v=0; v<n; ++v) {
            int x=v; while(x!=-1 && x!=u) x=info.parent[x];
            bool descendant=x==u; size += descendant;
            assert(et.is_ancestor(u,v)==descendant);
            auto [l,r] = hld.subtree(u);
            assert((l<=hld.pos[v] && hld.pos[v]<r)==descendant);
            assert((traversal.tin[u]<=traversal.tin[v] && traversal.tout[v]<=traversal.tout[u])==descendant);
        }
        assert(info.subtree_size[u]==size && et.tout[u]-et.tin[u]==size && hld.size[u]==size);
        for(int k=0; k<=n+2; ++k) {
            int expected=u;
            for(int i=0; i<k && expected!=-1; ++i) expected=info.parent[expected];
            assert(lca.ancestor(u,k)==expected);
        }
        assert(lca.ancestor(u,INT_MAX)==-1);
        for(int v=0; v<n; ++v) {
            int a=u,b=v;
            while(info.depth[a]>info.depth[b]) a=info.parent[a];
            while(info.depth[b]>info.depth[a]) b=info.parent[b];
            while(a!=b) { a=info.parent[a]; b=info.parent[b]; }
            assert(lca.query(u,v)==a && hld.lca(u,v)==a);
            assert(lca.distance(u,v)==depth[v]); diameter=max(diameter,depth[v]);
            vector<int> expected;
            for(int x=v; x!=-1; x=parent[x]) expected.push_back(x);
            reverse(expected.begin(),expected.end());
            for(bool edge : {false,true}) {
                vector<int> actual;
                for(auto s : hld.path(u,v,edge)) {
                    assert(0<=s.l && s.l<s.r && s.r<=n);
                    if(s.reverse) for(int i=s.r-1; i>=s.l; --i) actual.push_back(hld.vertex[i]);
                    else for(int i=s.l; i<s.r; ++i) actual.push_back(hld.vertex[i]);
                }
                auto want=expected;
                if(edge) want.erase(find(want.begin(),want.end(),a));
                assert(actual==want); // 順序一致により非可換な連結も検証。
            }
        }
    }
    auto d=tree_diameter(g);
    assert(d.length==diameter && static_cast<int>(d.path.size())==diameter+1);
    assert(d.path.front()==d.from && d.path.back()==d.to);
    for(int i=1; i<static_cast<int>(d.path.size()); ++i)
        assert(find(g[d.path[i-1]].begin(),g[d.path[i-1]].end(),d.path[i])!=g[d.path[i-1]].end());
}

void noncommutative_rerooting() {
    for(int trial=0; trial<60; ++trial) {
        int n=1+static_cast<int>(rng()%14);
        auto tree=make_tree(n,2);
        vector<vector<pair<int,int>>> g(n);
        for(int v=0; v<n; ++v) for(int to : tree[v]) g[v].push_back({to,min(v,to)*n+max(v,to)});
        auto add=[](string s,int v) { return "("+to_string(v)+s+")"; };
        auto lift=[](string s,int from,int to,int id) {
            return "["+to_string(from)+">"+to_string(to)+":"+to_string(id)+s+"]";
        };
        auto actual=rerooting(g,string(),[](string a,string b){return a+b;},add,lift,static_cast<int>(rng()%n));
        function<string(int,int)> naive=[&](int v,int p) {
            string s;
            for(auto [to,id] : g[v]) if(to!=p) s+=lift(naive(to,v),to,v,id);
            return add(s,v);
        };
        for(int v=0; v<n; ++v) assert(actual[v]==naive(v,-1));
    }
}

void large_tree(int shape) {
    int n=200000;
    auto g=make_tree(n,shape);
    vector<int> expected_centroids;
    if(shape == 0) expected_centroids = {n / 2 - 1,n / 2};
    else expected_centroids = {0};
    assert(tree_centroids(g) == expected_centroids);
    TreeInfo t(g); LCA lca(g); EulerTour e(g); HLD h(g);
    auto d=tree_diameter(g); auto r=dfs(g,0);
    assert(t.subtree_size[0]==n && e.tout[0]==n && h.subtree(0).second==n);
    assert(d.length==(shape==0 ? n-1 : 2));
    assert(lca.distance(n-1,n-2)==(shape==0 ? 1 : 2));
    assert(r.postorder.size()==g.size());
    vector<vector<pair<int,int>>> edges(n);
    for(int v=0; v<n; ++v) for(int to : g[v]) edges[v].push_back({to,0});
    auto result=rerooting(edges,0LL,[](ll a,ll b){return max(a,b);},
        [](ll a,int){return a;},[](ll a,int,int,int){return a+1;});
    assert(result[0]==(shape==0 ? n-1 : 1));
    assert(result[n-1]==(shape==0 ? n-1 : 2));
    cout << (shape==0 ? "path" : "star") << ": 200000 vertices passed\n";
}

int main() {
    assert(tree_centroids({}).empty());
    assert((tree_centroids({{}}) == vector<int>{0}));
    assert((tree_centroids({{1},{0}}) == vector<int>{0,1}));
    assert(TreeInfo({}).order.empty() && EulerTour({}).order.empty() && HLD({}).pos.empty());
    assert(tree_vertex_sums({},{}).empty() && tree_diameter({}).from==-1);
    vector<vector<pair<int,int>>> empty;
    assert(rerooting(empty,0,[](int a,int b){return a+b;},[](int a,int){return a+1;},
                     [](int a,int,int,int){return a;}).empty());
    for(int shape=0; shape<3; ++shape) for(int trial=0; trial<100; ++trial) {
        int n=1+static_cast<int>(rng()%35); small_tree(make_tree(n,shape),static_cast<int>(rng()%n));
    }
    assert((tree_vertex_sums({{1},{0,2},{1}}, {-1,0,-2})==vector<ll>{-1,-1,-3}));
    noncommutative_rerooting(); large_tree(0); large_tree(1);
    cout << "tree: 300 small trees and noncommutative rerooting passed\n";
}
