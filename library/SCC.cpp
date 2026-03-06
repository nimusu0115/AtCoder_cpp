#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define ALL(a)  (a).begin(),(a).end()
vector<vector<int>> G;
vector<vector<int>> rG;
vector<int> order;
vector<bool> seen;
vector<int> comp;
int N;

void dfs_scc1(int start){
    seen[start] = true;

    for(auto next : G[start]){
        if(seen[next]) continue;
        dfs_scc1(next);
    }

    order.push_back(start);
}

void dfs_scc2(int start,int k){
    comp[start] = k;

    for(auto next : rG[start]){
        if(comp[next] != -1) continue;
        dfs_scc2(next,k);
    }
}

vector<int> scc(){
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
    int M;
    cin >> N >> M;
    G.resize(N,vector<int>{});
    rG.resize(N,vector<int>{});
    order.resize({});
    seen.resize(N,false);
    comp.resize(N,-1);

    rep(i,M){
        int a,b;
        cin >> a >> b;
        a--;b--;
        G[a].push_back(b);
        rG[b].push_back(a);
    }

    vector<int> res = scc();

    vector<ll> cnt(N,0);
    rep(i,N) cnt[res[i]]++;

    ll ans = 0;
    rep(i,N) ans += cnt[i] * (cnt[i] - 1) / 2;

    cout << ans << endl;

}