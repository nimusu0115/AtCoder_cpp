#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i = 0;i < n;i++)
vector<vector<int>> G;
vector<bool> seen;
vector<int> first_order;
vector<int> last_order;
vector<int> depth;
int ptr;

//DFS
void dfs(int start){
    seen[start] = true;

    for(auto next : G[start]){
        if(seen[next]) continue;
        dfs(next);
    }
}

//タイムスタンプ
void dfs_order(int start){
    first_order[start] = ptr++;

    for(auto next : G[start]){
        if(first_order[next] != -1) continue;
        dfs_order(next);
    }

    last_order[start] = ptr++;
}

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
    int N,M;
    cin >> N >> M;

    G.assign(N,vector<int>{});
    rep(i,M){
        int a,b;
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }
}