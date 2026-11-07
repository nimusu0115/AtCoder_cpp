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

int main() {
    int N,M;
    cin >> N >> M;

    vector<vector<int>> G(N * (1<<10));
    rep(i,M){
        int a,b,w;
        cin >> a >> b >> w;
        a--,b--;

        rep(j,(1<<10)) G[a * (1<<10) + j].push_back(b * (1<<10) + (j ^ w));
    }

    auto dist = bfs(G,0);

    int ans = inf;
    rep(i,(1<<10)) if(dist[(N - 1) * (1<<10) + i] != -1) chmin(ans,i);

    if(ans != inf) cout << ans << endl;
    else cout << -1 << endl;
}