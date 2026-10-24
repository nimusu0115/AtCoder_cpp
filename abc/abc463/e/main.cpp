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
    ll N,M,Y;
    cin >> N >> M >> Y;

    vector<vector<pair<int,ll>>> G(N + 1);
    rep(i,M){
        ll u,v,T;
        cin >> u >> v >> T;
        u--,v--;

        G[u].push_back({v,T});
        G[v].push_back({u,T});
    }
    
    vector<ll> X(N);
    rep(i,N) cin >> X[i];
    rep(i,N){
        G[i].push_back({N,X[i]});
        G[N].push_back({i,X[i] + Y});
    }

    vector<ll> dist = dijkstra(G,0);

    rep(i,N){
        if(i == 0) continue;
        cout << dist[i];
        if(i < N - 1) cout << " ";
    }
    cout << endl;
}