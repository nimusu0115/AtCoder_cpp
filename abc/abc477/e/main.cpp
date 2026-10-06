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
vector<vector<pair<int,ll>>> weighted_graph;
vector<bool> seen;
vector<ll> dist;
vector<bool> kakutei;

void dijkstra(int start){
	dist.assign(weighted_graph.size(), numeric_limits<ll>::max());
	kakutei.assign(weighted_graph.size(), false);
	priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;
	Q.push({0,start});
	dist[start] = 0;
	while(!Q.empty()){
		int pos = Q.top().second;
		Q.pop();
		if(kakutei[pos]) continue;
		kakutei[pos] = true;
		for(auto v : weighted_graph[pos]){
			int to = v.first;
			ll cost = v.second;
			if(dist[to] <= dist[pos] + cost) continue;
			chmin(dist[to],dist[pos] + cost);
			Q.push({dist[to],to});
        }
    }
}

int main() {
    int N,Q;
    cin >> N >> Q;
    vector<ll> A(N),B(N);
    rep(i,N) cin >> A[i];
    rep(i,N) cin >> B[i];


    weighted_graph.assign(N + 1,vector<pair<int,ll>>{});
    dist.assign(N + 1,llinf);
    rep(i,N){
        weighted_graph[i].push_back({(i + 1) % N,A[i]});
        weighted_graph[(i + 1) % N].push_back({i,A[i]});

        weighted_graph[i].push_back({N,B[i]});
        weighted_graph[N].push_back({i,B[i]});
    }

    dijkstra(N);

    vector<ll> C(N + 1,0);
    rep(i,N) C[i + 1] = A[i];
    onerep(i,N){
        if(i == 1) continue;
        C[i] += C[i - 1];
    }

    while(Q > 0){
        Q--;

        int S,T;
        cin >> S >> T;
        S--,T--;

        if(S > T) swap(S,T);
        ll r = C[T] - C[S];
        ll l = C[N] - r;
        ll cntr = dist[S] + dist[T];
        if(T == N) cout << dist[S] << endl;
        else cout << min(min(l,r),cntr) << endl;
    }

}