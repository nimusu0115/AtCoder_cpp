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
    int N = G.size();
    vector<ll> score(G.size(),llinf);
    vector<bool> seen(N,false);
    if(G.empty()) return score;
    assert(0 <= start && start < static_cast<int>(G.size()));
    priority_queue<tuple<int,int,int>,vector<tuple<int,int,int>>,greater<tuple<int,int,int>>> Q;

    score[start] = 0;
    seen[start] = true;
    int rank = 0;
    int prev = 0;
    Q.push({rank,0,start});
    while(!Q.empty()){
        int pos = get<2>(Q.top());
        Q.pop();
        rank++;
        if(seen[pos]) continue;
        rep(i,G[pos].size()){
            int to = G[pos][i].first;
            int cost = G[pos][i].second;
            assert(cost >= 0);
            seen[to] = true;
            Q.push({rank,cost,to});
        }
    }
    return score;
}

int main() {
    int N,M;
    cin >> N >> M;
    vector<vector<pair<int,int>>> G(N);
    rep(i,M){
        int a,b,c;
        cin >> a >> b >> c;
        a--,b--;
        G[a].push_back({c,b});
    }
}