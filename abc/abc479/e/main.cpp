#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
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
};

int main() {
    int N;
    cin >> N;
    vector<int> A(N - 1),B(N - 1);
    rep(i,N - 1) cin >> A[i] >> B[i];
    rep(i,N - 1) A[i]--,B[i]--;

    vector<vector<int>> G(N,vector<int>({}));
    rep(i,N - 1){
        G[A[i]].push_back(B[i]);
        G[B[i]].push_back(A[i]);
    }

    TreeInfo Info(G);

    int ctr = 0;
    rep(i,N){
        int max = N - Info.subtree_size[i];
        for(int to : G[i]) if(Info.depth[to] > Info.depth[i]) chmax(max,Info.subtree_size[to]);

        if(max < (N + 1) / 2) ctr = i;
    }

    TreeInfo info(G,ctr);

    vector<ll> imos(N,0);
    rep(i,N - 1){
        if(info.depth[A[i]] < info.depth[B[i]]) swap(A[i],B[i]);
        imos[A[i]] += i + 1;
    }

    vector<ll> ans = tree_vertex_sums(G,imos,ctr);

    rep(i,N){
        cout << 1LL * N * (N - 1) / 2 - ans[i];
        if(i != N - 1) cout << " ";
    }
    cout << endl;
}