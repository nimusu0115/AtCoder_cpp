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
vector<vector<int>> G;
vector<bool> seen;
vector<int> dist;
vector<bool> kakutei;
//距離計算
void bfs_dist(int start){
  queue<int> Q;
  Q.push(start);
  dist[start] = 0;
  while(!Q.empty()){
    int pos = Q.front();
    Q.pop();
    for(int to : G[pos]){
      if(dist[to] == -1){
        int m = 0;
        for(int tto : G[to]){
            chmax(m,dist[tto]);
        }
        dist[to] = m + 1;
        Q.push(to);
      }
    }
  }
}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        int N,M;
        cin >> N >> M;

        G.assign(N,vector<int>{});
        dist.resize(N,-1);
        rep(i,M){
            int a,b;
            cin >> a >> b;
            G[a - 1].push_back(b - 1);
            G[b - 1].push_back(a - 1);
        }

        bfs_dist(0);
        rep(i,N){
            cout << dist[i];
            if(i != N - 1) cout << " ";
        }
        cout << endl;
    }
}