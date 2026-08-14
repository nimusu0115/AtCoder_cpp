#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i = 0;i < n;i++)
vector<vector<int>> G;
vector<bool> seen;
vector<int> first_order;
vector<int> last_order;
vector<int> depth;
int ptr;

// start から深さ優先探索し、到達できる頂点を seen=true にする。
// 前提: seen は頂点数と同じサイズの false で初期化されている。
void dfs(int start){
    seen[start] = true;

    for(auto next : G[start]){
        if(seen[next]) continue;
        dfs(next);
    }
}

// DFSで頂点に入った時刻を first_order、出た時刻を last_order に記録する。
// 前提: first_order と last_order は -1、ptr は 0 で初期化されている。
void dfs_order(int start){
    first_order[start] = ptr++;

    for(auto next : G[start]){
        if(first_order[next] != -1) continue;
        dfs_order(next);
    }

    last_order[start] = ptr++;
}

// start を深さ d としてDFSし、各頂点の深さを depth に記録する。
// 前提: seen は false で初期化されている。
void dfs_depth(int start, int d){
    seen[start] = true;
    depth[start] = d;

    for(auto next : G[start]){
        if(seen[next]) continue;
        dfs_depth(next, d + 1);
    }
}

// 無向グラフを入力して G を構築する使用例。
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
