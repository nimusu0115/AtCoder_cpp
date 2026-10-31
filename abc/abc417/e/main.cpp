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
// 無重みグラフの最短辺数。到達不能=-1。O(V+E)、空グラフは空配列。
vector<int> bfs(const vector<vector<int>>& G,int start){
    int N = static_cast<int>(G.size());
    vector<int> dist(N,-1);
    if(N == 0) return dist;
    assert(0 <= start && start < N);
    queue<int> Q;
    dist[start] = 0;
    Q.push(start);
    while(!Q.empty()){
        int pos = Q.front();
        Q.pop();
        for(int to : G[pos]){
            if(dist[to] != -1) continue;
            dist[to] = dist[pos] + 1;
            Q.push(to);
        }
    }
    return dist;
}

vector<int> solve(vector<vector<int>> G,int start,int goal){
    int pos = start;
    vector<int> res;
    res.push_back(start);

    while(true){
        for(auto to : G[pos]){
            vector<vector<int>> g = G;
            for(auto r : res){
                for(auto p : g[r]){
                }
            }
        }
    }
}

int main() {
    int T;
    cin >> T;

    while(T > 0){
        T--;

        int N,M,X,Y;
        cin >> N >> M >> X >> Y;
        vector<int> U(M),V(M);
        rep(i,M){
            cin >> U[i] >> V[i];
            U[i]--,V[i]--;
        }

        vector<vector<int>> G(N);
        rep(i,M){
            G[U[i]].push_back(V[i]);
            G[V[i]].push_back(U[i]);
        }

        rep(i,N) sort(ALL(G[i]));
    }
}