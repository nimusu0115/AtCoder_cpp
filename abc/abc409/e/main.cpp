#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

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

int main() {
    int N;
    cin >> N;
    vector<ll> x(N),u(N - 1),v(N - 1),w(N - 1);
    rep(i,N) cin >> x[i];
    rep(i,N - 1) cin >> u[i] >> v[i] >> w[i];
    rep(i,N - 1) u[i]--,v[i]--;

    vector<vector<int>> G(N);
    rep(i,N - 1){
        G[u[i]].push_back(v[i]);
        G[v[i]].push_back(u[i]);
    }
    map<pair<int,int>,ll> m;
    rep(i,N - 1){
        m[{u[i],v[i]}] = w[i];
        m[{v[i],u[i]}] = w[i];
    }

    TreeInfo tree = TreeInfo(G,0);
    auto depth = tree.depth;
    auto order = tree.order;
    reverse(ALL(order));
    auto parent = tree.parent;

    vector<ll> sum = x;
    rep(i,N){
        for(auto to : G[order[i]]){
            if(to == parent[order[i]]) continue;
            sum[order[i]] += sum[to];
        }
    }

    ll ans = 0;
    rep(i,N){
        if(parent[i] == -1) continue;
        ans += m[{i,parent[i]}] * abs(sum[i]);
    }

    cout << ans << endl;
}