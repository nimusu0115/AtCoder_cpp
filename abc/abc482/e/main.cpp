//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i,n) for(ll i = 0;i < n;i++)
#define rrep(i,n) for(ll i = n - 1;i >= 0;i--)
#define onerep(i,n) for(ll i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}
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

        if(N == 0) return;
        assert(0 <= root && root < N);

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
        assert(0 <= v && v < N && k >= 0);
        if(k > depth[v]) return -1;
        for(int i = 0;i < LOG && v != -1;i++){
            if((k>>i) & 1) v = parent[i][v];
        }
        return v;
    }

    // 頂点 u と v の最小共通祖先を返す。
    int query(int u,int v) const{
        assert(0 <= u && u < N && 0 <= v && v < N);
        assert(depth[u] >= 0 && depth[v] >= 0);
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


int main() {
    int N;
    cin >> N;
    vector<vector<int>> G(N);
    rep(i,N - 1){
        int u,v;
        cin >> u >> v;
        u--,v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    vector<int> C(N);
    rep(i,N) cin >> C[i];

    vector<int> tyusin;

    TreeDiameter TT = tree_diameter(G);

    if(TT.length % 2 == 1){
        vector<int> gg = {TT.path[TT.length / 2],TT.path[TT.length / 2 + 1]};
        G.push_back(gg);
        auto g = G[TT.path[TT.length / 2]];
        G[TT.path[TT.length / 2]].clear();
        for(auto v : g) if(v != TT.path[TT.length / 2 + 1]) G[TT.path[TT.length / 2]].push_back(v);
        G[TT.path[TT.length / 2]].push_back(N);

        auto g2 = G[TT.path[TT.length / 2 + 1]];
        G[TT.path[TT.length / 2 + 1]].clear();
        for(auto v : g2) if(v != TT.path[TT.length / 2]) G[TT.path[TT.length / 2 + 1]].push_back(v);
        G[TT.path[TT.length / 2 + 1]].push_back(N);

        N++;
    }


    TreeDiameter T = tree_diameter(G);

    int ctr = T.path[T.length / 2];
    for(auto v : G[ctr]) tyusin.push_back(v);
    map<int,int> tyusinToNum;
    rep(i,tyusin.size()){
        tyusinToNum[tyusin[i]] = i;
    }

    vector<map<int,int>> cs(tyusin.size());

    LCA Tlca(G,ctr);
    rep(i,N){
        if(Tlca.ancestor(i,T.length / 2) == ctr){
            cs[tyusinToNum[Tlca.ancestor(i,T.length / 2 - 1)]][C[i]]++;
        }
    }

    map<ll,ll> Cs;
    rep(i,N){
        if(Tlca.depth[i] == T.length / 2) Cs[C[i]]++;
    }

    ll ans = 0;
    for(auto v : Cs){
        ans += 1LL * v.second * (v.second - 1) / 2;
    }

    rep(i,cs.size()){
        for(auto v : cs[i]){
            ans -= 1LL * v.second * (v.second - 1) / 2;
        }
    }

    cout << ans << endl;
}