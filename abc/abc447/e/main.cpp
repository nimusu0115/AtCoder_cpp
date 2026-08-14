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
ll prm = 998244353;

int N;
vector<int> U,V;
void bfs_seen(int start,const vector<vector<int>>& G,vector<bool>& seen){
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

bool solve(int m){
    vector<vector<int>> G(N,vector<int>{});
    rep(i,m){
        G[U[i]].push_back(V[i]);
        G[V[i]].push_back(U[i]);
    }
    vector<bool> seen(N,false);
    bfs_seen(U[0],G,seen);
    bool res = true;
    rep(i,N) if(!seen[i]) res = false;
    return res;
}
struct UnionFind{
  map<int,int> par;

    UnionFind(int H){
    rep(i,H) par[i] = i;
  }

  int root(int x){
    if(par[x] == x) return x;
    return par[x] = root(par[x]);
  }

    void unite(int x,int y){
    int rx = root(x);
    int ry = root(y);
    if(rx == ry) return;
    par[rx] = ry;
  }

    bool same(int x,int y){
    int rx = root(x);
    int ry = root(y);
    return rx == ry;
  }
};

long long modpow(long long a, long long n, long long mod) {
	long long res = 1;
	while (n > 0) {
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}

int main() {
    int M;
    cin >> N >> M;

    vector<vector<int>> G(N,vector<int>{});
    U.resize(M);
    V.resize(M);
    rep(i,M){
        int u,v;
        cin >> u >> v;
        U[i] = u - 1;
        V[i] = v - 1;
    }
    reverse(ALL(U));
    reverse(ALL(V));

    int ok = 0,ng = M;
    while(ok + 1 != ng){
        int m = (ng + ok) / 2;
        if(solve(m)) ng = m;
        else ok = m;
    }

    vector<bool> pickup(M,true);
    rep(i,ok) pickup[i] = false;

    UnionFind P(N);
    rep(i,ok) P.unite(U[i],V[i]);
    rep(i,M){
        if(P.same(U[i],V[i])) pickup[i] = false;
        else pickup[i] = true;
    }

    reverse(ALL(pickup));

    ll ans = 0;
    rep(i,M){
        if(pickup[i]) ans = (ans + modpow(2,i + 1,prm)) % prm;
    }

    cout << ans << endl;
}