#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

void dijkstra(int start,const vector<vector<pair<int,ll>>>& G,vector<ll>& dist,vector<bool>& kakutei){
  priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> Q;
  Q.push({0,start});
  dist[start] = 0;
  kakutei[start] = 0;
  while(!Q.empty()){
    int pos = Q.top().second;
    Q.pop();
    if(kakutei[pos]) continue;
    kakutei[pos] = true;
    for(auto v : G[pos]){
        int to = v.first;
        ll cost = v.second;
        if(dist[to] <= dist[pos] + cost) continue;
        chmin(dist[to],dist[pos] + cost);
        Q.push({dist[to],to});
        }
    }
}

int main() {
    int N,M,T;
    cin >> N >> M >> T;
    vector<vector<pair<int,ll>>> G(N,vector<pair<int,ll>>{});
    rep(i,M){
        ll a,b,c;
        cin >> a >> b >> c;
        G[a - 1].push_back({b - 1,c});
        G[b - 1].push_back({a - 1,c});
    }

    vector<ll> dist(N,llinf);
    vector<bool> kakutei(N,false);

    dijkstra(0,G,dist,kakutei);

    if(dist[T - 1] == llinf) cout << -1 << endl;
    else cout << 2 * dist[T - 1] << endl;

}