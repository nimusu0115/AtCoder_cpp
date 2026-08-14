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
void bfs_dist(int start,const vector<vector<int>>& G,vector<ll>& dist,vector<ll> V){
  queue<int> Q;
  Q.push(start);
  dist[start] = V[start];
  while(!Q.empty()){
    int pos = Q.front();
    Q.pop();
    for(int to : G[pos]){
      if(dist[to] == -1){
        dist[to] = dist[pos] + V[to];
        Q.push(to);
      }
    }
  }
}

int main() {
    int N,Q;
    cin >> N >> Q;
    vector<ll> V(N),P(N),X(Q);
    rep(i,N) cin >> V[i];
    onerep(i,N - 1) cin >> P[i];
    rep(i,Q) cin >> X[i];

    vector<vector<int>> G(N,vector<int>{});
    vector<ll> dist(N,-1);
    rep(i,N){
        if(i == 0) continue;
        G[P[i] - 1].push_back(i);
    }
    bfs_dist(0,G,dist,V);
    
    rep(i,Q) cout << dist[X[i] - 1] << endl;
}