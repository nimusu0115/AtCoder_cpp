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
vector<ll> dist;
vector<bool> kakutei;
//到達可能性
void bfs_seen(int start){
  queue<int> Q;
  Q.push(start);
  seen[start] = true;
  while(!Q.empty()){
    int pos = Q.front();
    Q.pop();
    for(int to : G[pos]){
      if(seen[to] == false){
        seen[to] = true;
        Q.push(to);
      }
    }
  }
}

int main() {
    int N,M;
    cin >> N >> M;
    vector<int> A(M),B(M);
    rep(i,M) cin >> A[i] >> B[i];

    G.resize(N,vector<int>{});
    seen.resize(N,false);
    rep(i,M) G[A[i] - 1].push_back(B[i] - 1);

    bfs_seen(0);

    int ans = 0;
    rep(i,N) if(seen[i]) ans++;

    cout << ans << endl;
}