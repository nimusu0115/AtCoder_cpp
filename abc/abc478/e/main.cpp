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
vector<vector<int>> G;

vector<int> topological_sort(const vector<vector<int>>& G){
    int N = static_cast<int>(G.size());
    vector<int> indegree(N,0);
    for(int from = 0;from < N;from++){
        for(int to : G[from]) indegree[to]++;
    }

    priority_queue<int,vector<int>,greater<int>> Q;
    for(int v = 0;v < N;v++){
        if(indegree[v] == 0) Q.push(v);
    }

    vector<int> order;
    while(!Q.empty()){
        int pos = Q.top();
        Q.pop();
        order.push_back(pos);

        for(int to : G[pos]){
            indegree[to]--;
            if(indegree[to] == 0) Q.push(to);
        }
    }

    if(static_cast<int>(order.size()) != N) return {};
    return order;
}

int main() {
    int N,Q;
    vector<int> t(Q),u(Q),v(Q);
    rep(i,Q) cin >> t[i] >> u[i] >> v[i]; 

    G.resize(N);
    rep(i,Q){
        G[]
    }
}