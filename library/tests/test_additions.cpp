#include "../graph/lowlink.cpp"
#include "../graph/kruskal.cpp"
#include "../graph/shortest_path.cpp"
#include "../graph/scc.cpp"
#include "../data_structure/weighted_union_find.cpp"
#include "../data_structure/sparse_table.cpp"
#include "../techniques/prefix_sum.cpp"
#include "../techniques/imos.cpp"
#include "../string/z_algorithm.cpp"

mt19937 rng(173);
using ll = long long;
int rnd(int n) { return static_cast<int>(rng()%n); }

int components(int n,const vector<pair<int,int>>& edges,int skip_vertex=-1,int skip_edge=-1) {
    vector<vector<int>> g(n);
    for(int i=0; i<static_cast<int>(edges.size()); ++i) {
        auto [u,v]=edges[i];
        if(i==skip_edge || u==skip_vertex || v==skip_vertex) continue;
        g[u].push_back(v); g[v].push_back(u);
    }
    vector<bool> seen(n); int count=0;
    for(int v=0; v<n; ++v) if(v!=skip_vertex && !seen[v]) {
        ++count; vector<int> stack={v}; seen[v]=true;
        while(!stack.empty()) {
            int u=stack.back(); stack.pop_back();
            for(int to : g[u]) if(!seen[to]) { seen[to]=true; stack.push_back(to); }
        }
    }
    return count;
}

void graph_tests() {
    assert(Lowlink(0,{}).bridges.empty() && kruskal(0,{}).connected());
    for(int trial=0; trial<1000; ++trial) {
        int n=1+rnd(8), m=rnd(13); vector<pair<int,int>> edges;
        for(int i=0; i<m; ++i) edges.push_back({rnd(n),rnd(n)});
        Lowlink actual(n,edges); int base=components(n,edges);
        vector<int> bridges,cut;
        for(int i=0; i<m; ++i) if(components(n,edges,-1,i)>base) bridges.push_back(i);
        for(int v=0; v<n; ++v) if(components(n,edges,v)>base) cut.push_back(v);
        sort(actual.bridges.begin(),actual.bridges.end());
        assert(actual.bridges==bridges && actual.articulation==cut);
    }
    for(int trial=0; trial<250; ++trial) {
        int n=1+rnd(6),m=rnd(11); vector<KruskalEdge> edges; vector<pair<int,int>> endpoints;
        for(int i=0; i<m; ++i) { int u=rnd(n),v=rnd(n); edges.push_back({u,v,rnd(21)-10}); endpoints.push_back({u,v}); }
        int target=components(n,endpoints); ll best=LLONG_MAX;
        for(int mask=0; mask<(1<<m); ++mask) {
            if(__builtin_popcount(static_cast<unsigned>(mask))!=n-target) continue;
            vector<pair<int,int>> selected; ll cost=0;
            for(int i=0; i<m; ++i) if(mask>>i&1) { selected.push_back(endpoints[i]); cost+=edges[i].cost; }
            if(components(n,selected)==target) best=min(best,cost);
        }
        auto actual=kruskal(n,edges);
        assert(actual.cost==best && actual.components==target && actual.connected()==(target==1));
        ll sum=0; vector<pair<int,int>> selected;
        for(int id : actual.edge_ids) { sum+=edges[id].cost; selected.push_back(endpoints[id]); }
        assert(sum==best && components(n,selected)==target && static_cast<int>(selected.size())==n-target);
    }
    // 中間費用がlong longを超えるが、最終費用は範囲内。
    auto wide=kruskal(4,{{0,1,LLONG_MIN/2-1},{1,2,LLONG_MIN/2-1},{2,3,LLONG_MAX}});
    assert(wide.cost==-3);
    for(int trial=0; trial<300; ++trial) {
        int n=1+rnd(18); vector<vector<pair<int,int>>> g(n);
        vector<vector<pair<int,ll>>> weighted(n);
        vector<vector<int>> d(n,vector<int>(n,100000));
        for(int v=0; v<n; ++v) {
            d[v][v]=0;
            for(int to=0; to<n; ++to) if(rnd(4)==0) {
                int w=rnd(2); g[v].push_back({to,w}); weighted[v].push_back({to,w}); d[v][to]=min(d[v][to],w);
            }
        }
        for(int k=0; k<n; ++k) for(int i=0; i<n; ++i) for(int j=0; j<n; ++j) d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
        for(int s=0; s<n; ++s) {
            auto actual=zero_one_bfs(g,s); auto dij=dijkstra(weighted,s);
            for(int v=0; v<n; ++v) {
                assert(actual[v]==(d[s][v]==100000 ? -1 : d[s][v]));
                assert(dij[v]==(d[s][v]==100000 ? LLONG_MAX : d[s][v]));
            }
        }
    }
    int n=200000;
    vector<pair<int,int>> path; vector<vector<int>> g(n);
    for(int v=1; v<n; ++v) { path.push_back({v-1,v}); g[v-1].push_back(v); }
    Lowlink large(n,path); assert(static_cast<int>(large.bridges.size())==n-1 && static_cast<int>(large.articulation.size())==n-2);
    auto ids=scc(g); assert(ids.front()==0 && ids.back()==n-1);
    g.back().push_back(0); ids=scc(g); for(int id : ids) assert(id==0);
    cout << "graph additions: 1000 lowlink, 250 exhaustive forest, 300 shortest-path cases; 200000-vertex path passed\n";
}

optional<ll> naive_diff(const vector<vector<pair<int,ll>>>& g,int x,int y) {
    vector<bool> seen(g.size()); vector<ll> potential(g.size());
    queue<int> q; q.push(x); seen[x]=true;
    while(!q.empty()) {
        int v=q.front(); q.pop();
        for(auto [to,w] : g[v]) if(!seen[to]) { seen[to]=true; potential[to]=potential[v]+w; q.push(to); }
    }
    if(!seen[y]) return nullopt;
    return potential[y];
}

void structure_tests() {
    WeightedUnionFind empty(0); SparseTable<int> es(vector<int>{});
    for(int trial=0; trial<150; ++trial) {
        int n=1+rnd(30); WeightedUnionFind uf(n);
        vector<vector<pair<int,ll>>> g(n); vector<ll> potential(n);
        for(ll& p : potential) p=rnd(2001)-1000;
        for(int step=0; step<150; ++step) {
            int x=rnd(n),y=rnd(n); auto before=naive_diff(g,x,y);
            ll w=potential[y]-potential[x];
            if(before && rnd(3)==0) {
                assert(!uf.unite(x,y,w+1)); assert(uf.diff(x,y)==before);
            } else {
                assert(uf.unite(x,y,w)); g[x].push_back({y,w}); g[y].push_back({x,-w});
            }
            for(int k=0; k<5; ++k) {
                int a=rnd(n),b=rnd(n); auto expected=naive_diff(g,a,b);
                assert(uf.diff(a,b)==expected && uf.same(a,b)==expected.has_value());
                int count=0; for(int v=0; v<n; ++v) count+=naive_diff(g,a,v).has_value();
                assert(uf.size(a)==count);
            }
        }
        vector<ll> a(n); for(ll& x : a) x=rnd(200)-100;
        SparseTable<ll> st(a);
        for(int l=0; l<n; ++l) for(int r=l+1; r<=n; ++r) assert(st.query(l,r)==*min_element(a.begin()+l,a.begin()+r));
    }
    WeightedUnionFind wide(3); assert(wide.unite(0,1,LLONG_MAX-5)); assert(wide.unite(1,2,-(LLONG_MAX-5)));
    assert(wide.diff(0,2)==0 && wide.diff(1,0)==-(LLONG_MAX-5));
    WeightedUnionFind negative(2); assert(negative.unite(0,1,LLONG_MIN)); assert(negative.diff(0,1)==LLONG_MIN);
    cout << "structures: 150 randomized weighted-UF and RMQ cases passed\n";
}

void technique_tests() {
    assert(PrefixSum({}).sum(0,0)==0 && PrefixSum2D({}).sum(0,0,0,0)==0);
    assert(Imos(0).build().empty() && Imos2D(0,0).build().empty());
    for(int trial=0; trial<200; ++trial) {
        int n=rnd(40); vector<ll> a(n); for(ll& x : a) x=rnd(31)-15;
        PrefixSum prefix(a); Imos imos(n); vector<ll> want(n);
        for(int l=0; l<=n; ++l) for(int r=l; r<=n; ++r) assert(prefix.sum(l,r)==accumulate(a.begin()+l,a.begin()+r,0LL));
        for(int i=0; i<60; ++i) {
            int l=rnd(n+1),r=rnd(n+1); if(l>r) swap(l,r); ll value=rnd(31)-15;
            imos.add(l,r,value); for(int j=l; j<r; ++j) want[j]+=value;
        }
        assert(imos.build()==want && imos.build()==want);
        imos.add(0,n,3); for(ll& x : want) x+=3; assert(imos.build()==want);
        int h=rnd(9),w=rnd(9);
        vector<vector<ll>> grid(h,vector<ll>(w)), expected(h,vector<ll>(w));
        for(auto& row : grid) for(ll& x : row) x=rnd(21)-10;
        PrefixSum2D p(grid); Imos2D im(h,w);
        for(int step=0; step<100; ++step) {
            int y1=rnd(h+1),y2=rnd(h+1),x1=rnd(w+1),x2=rnd(w+1);
            if(y1>y2) swap(y1,y2);
            if(x1>x2) swap(x1,x2);
            ll value=rnd(21)-10,sum=0;
            for(int y=y1; y<y2; ++y) for(int x=x1; x<x2; ++x) { sum+=grid[y][x]; expected[y][x]+=value; }
            // 空のvectorでは列数情報がないためw=0として扱う。
            assert(p.sum(y1,h ? x1 : 0,y2,h ? x2 : 0)==sum);
            im.add(y1,x1,y2,x2,value);
        }
        assert(im.build()==expected && im.build()==expected);
        string s; for(int i=0; i<n; ++i) s+=static_cast<char>('a'+rnd(4));
        auto z=z_algorithm(s); assert(z.size()==s.size());
        for(int i=0; i<n; ++i) { int length=0; while(i+length<n && s[length]==s[i+length]) ++length; assert(z[i]==length); }
    }
    PrefixSum wide({-LLONG_MAX,LLONG_MAX,LLONG_MAX}); assert(wide.sum(1,2)==LLONG_MAX);
    PrefixSum2D p({{-LLONG_MAX,LLONG_MAX},{LLONG_MAX,0}}); assert(p.sum(1,0,2,2)==LLONG_MAX);
    Imos im(2); im.add(0,2,-LLONG_MAX); assert((im.build()==vector<ll>{-LLONG_MAX,-LLONG_MAX}));
    Imos2D im2(1,1); im2.add(0,0,1,1,-LLONG_MAX); assert(im2.build()[0][0]==-LLONG_MAX);
    cout << "techniques: 200 randomized prefix/imos/Z cases passed\n";
}

int main() { graph_tests(); structure_tests(); technique_tests(); }
