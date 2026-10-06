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
vector<vector<int>> G;
vector<vector<int>> rG;
vector<int> order;
vector<bool> seen;
vector<int> comp;

// 元のグラフ G をDFSし、帰りがけ順に頂点を order へ追加する。
void dfs_scc1(int start){
    seen[start] = true;

    for(auto next : G[start]){
        if(seen[next]) continue;
        dfs_scc1(next);
    }

    order.push_back(start);
}

// 逆向きグラフ rG をDFSし、同じ強連結成分の頂点に成分番号 k を付ける。
void dfs_scc2(int start,int k){
    comp[start] = k;

    for(auto next : rG[start]){
        if(comp[next] != -1) continue;
        dfs_scc2(next,k);
    }
}
// Kosaraju法で強連結成分分解を行い、各頂点の成分番号を返す。
// G と rG は同じ有向辺を互いに逆向きで保持している必要がある。
// 戻り値の成分番号は、成分を縮約したDAGのトポロジカル順になる。
vector<int> scc(){
    int N = static_cast<int>(G.size());
    order.clear();
    seen.assign(N, false);
    comp.assign(N, -1);
    rep(i,N) if(!seen[i]) dfs_scc1(i);
    reverse(ALL(order));

    int group_id = 0;
    for(int v : order){
        if(comp[v] == -1){
            dfs_scc2(v,group_id);
            group_id++;
        }
    }

    vector<int> res(N);
    rep(i,N) res[i] = comp[i];
    return res;
}

int main() {
    int N,Q;
    cin >> N >> Q;
    vector<int> t(Q),u(Q),v(Q);
    rep(i,Q) cin >> t[i] >> u[i] >> v[i]; 

    rep(i,Q) u[i]--,v[i]--;

    G.assign(N,{});
    rG.assign(N,{});
    rep(i,Q){
        G[u[i]].push_back(v[i]);
        rG[v[i]].push_back(u[i]);
    }

    scc();
    vector<int> ans(N);
    rep(i,N) ans[i] = comp[i];

    bool flg = true;
    rep(i,Q){
        if(t[i] == 0){
            if(ans[u[i]] > ans[v[i]]) flg = false;
        }
        if(t[i] == 1){
            if(ans[u[i]] >= ans[v[i]]) flg = false;
        }
    }
    if(flg){
        cout << "Yes" << endl;
        rep(i,N){
            cout << ans[i] + 1;
            if(i != N - 1) cout << " ";
        }
        cout << endl;
    }
    else{
        cout << "No" << endl;
    }
}