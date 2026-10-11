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
vector<int> Centroid(const vector<vector<int>> &g) {
        int n = g.size();
        vector<int> centroid;
        vector<int> sz(n);
        function<void (int, int)> dfs = [&](int u, int prev) {
                sz[u] = 1;
                bool is_centroid = true;
                for (auto v : g[u]) if (v != prev) {
                        dfs(v, u);
                        sz[u] += sz[v];
                        if (sz[v] > n / 2) is_centroid = false;
                }
                if (n - sz[u] > n / 2) is_centroid = false;
                if (is_centroid) centroid.push_back(u);
        };
        dfs(0, -1);
        return centroid;
}


int main() {
    int n;
    cin >> n;
    vector<int> A(n - 1),B(n - 1);
    rep(i,n - 1) cin >> A[i] >> B[i];
    rep(i,n - 1) A[i]--,B[i]--;

    vector<vector<int>> g(n,vector<int>({}));
    rep(i,n - 1){
        g[A[i]].push_back(B[i]);
        g[B[i]].push_back(A[i]);
    }

    vector<int> ctr = Centroid(g);
    int c = ctr[0];
    set<int> S;
    for(int v : g[c]){
        S.insert(v);
    }

    g[c].clear();

    dsu uf(n);
    rep(i,n - 1){
        if(A[i] == c || B[i] == c) continue;
        uf.merge(A[i],B[i]);
    }

    map<int,int> cost;
    rep(i,n - 1){
        if(A[i] == c){
            cost[uf.leader(B[i])] += i + 1;
        }
        else{
            cost[uf.leader(A[i])] += i + 1;
        }
    }

    int costsum = n * (n - 1) / 2;

    rep(i,n){
        if(i == c) cout << costsum;
        else cout << costsum - cost[uf.leader(i)];
        if(i != n - 1) cout << " ";
    }
    cout << endl;
    //for(auto v : cost) cout << v.first << " " << v.second << endl;
    //cout << uf.groups().size() << endl;
    //rep(i,n) cout << uf.leader(i) << endl;
}