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
vector<bool> ans;
vector<ll> A;
void bfs_seen(int start){
  queue<int> Q;
  Q.push(start);
  ans[start] = false;
  seen[start] = true;
  while(!Q.empty()){
    int pos = Q.front();
    Q.pop();
    for(int to : G[pos]){
      if(!seen[to]){
        seen[to] = true;
        if(ans[pos] || A[start] == A[to]) ans[to] = true;
        Q.push(to);
      }
    }
  }
}

int main() {
    int N;
    cin >> N;
    A.resize(N);
    rep(i,N) cin >> A[i];

    G.resize(N,vector<int>{});
    seen.resize(N);
    ans.resize(N,false);
    rep(i,N - 1){
        int a,b;
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }
    bfs_seen(0);
    rep(i,N){
        if(ans[i]) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}