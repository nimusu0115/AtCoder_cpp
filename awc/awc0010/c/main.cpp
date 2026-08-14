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

int main() {
    ll N,K,Q;
    cin >> N >> K >> Q;
    vector<ll> A(N),L(Q),R(Q);
    rep(i,N) cin >> A[i];
    rep(i,Q) cin >> L[i] >> R[i];

    UnionFind U(N);
    rep(i,N - 1){
        if(abs(A[i] - A[i + 1]) <= K) U.unite(i,i + 1);
    }

    rep(i,Q){
        if(U.same(L[i] - 1,R[i] - 1)) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

}