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
vector<int> first_order;
vector<int> last_order;
vector<int> depth;
int ptr;

//深さ計算
void dfs_depth(int start, int d){
    seen[start] = true;
    depth[start] = d;

    for(auto next : G[start]){
        if(seen[next]) continue;
        dfs_depth(next, d + 1);
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
		seen.assign(N,false);
        depth.assign(N,0);
        rep(i,M){
            int a,b;
            cin >> a >> b;
            G[a - 1].push_back(b - 1);
            G[b - 1].push_back(a - 1);
        }

        dfs_depth(0,0);
        rep(i,N){
            cout << depth[i];
            if(i != N - 1) cout << " ";
        }
        cout << endl;
    }
}