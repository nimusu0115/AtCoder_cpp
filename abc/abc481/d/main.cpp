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

// G[v] = {行き先, 非負long long重み}。到達不能/表現範囲外=LLONG_MAX。
// 有限距離はLLONG_MAX未満。加算前に範囲を確認する。O((V+E)log(E+2))。
vector<ll> dijkstra(const vector<vector<pair<int,ll>>>& G,int start){
    const ll llinf = numeric_limits<ll>::max();
    vector<ll> dist(G.size(),llinf);
    if(G.empty()) return dist;
    assert(0 <= start && start < static_cast<int>(G.size()));
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;
    dist[start] = 0;
    Q.push({0,start});
    while(!Q.empty()){
        ll distance = Q.top().first;
        int pos = Q.top().second;
        Q.pop();
        if(distance != dist[pos]) continue;
        for(auto edge : G[pos]){
            int to = edge.first;
            ll cost = edge.second;
            assert(cost >= 0);
            if(cost >= llinf - distance || distance + cost >= dist[to]) continue;
            dist[to] = distance + cost;
            Q.push({dist[to],to});
        }
    }
    return dist;
}

int main() {
    ll N,M,S,T;
    cin >> N >> M >> S >> T;

    vector<vector<pair<int,ll>>> g(N),G(N);

    vector<int> A(M),B(M);
    rep(i,M){
        int a,b;
        cin >> a >> b;
        a--,b--;
        g[a].push_back({b,1});
    }

    rep(i,N){
        int m = inf;
        for(auto v : g[i]) chmin(m,v.first);
        if(m != inf){
            for(auto v : g[i]){
                if(v.first == m) G[i].push_back({m,0});
                else G[i].push_back({v.first,1});
            }
        }
    }

    vector<ll> dist = dijkstra(G,S - 1);

    if(dist[T - 1] < inf) cout << dist[T - 1] << endl;
    else cout << -1 << endl;
}