#include<bits/stdc++.h>
using namespace std;

// 無重みグラフの最短辺数。到達不能=-1。O(V+E)、空グラフは空配列。
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

// 多始点BFS。各頂点までの「最も近い始点からの距離」を返す。到達不能=-1。
// 始点はすべて距離0、重複可。始点が空なら全頂点-1。空グラフは空配列。
// 始点数をKとしてO(V+E+K)。非空グラフでは始点が有効な頂点番号であること。
vector<int> multi_source_bfs(const vector<vector<int>>& G,const vector<int>& starts){
    int N = static_cast<int>(G.size());
    vector<int> dist(N,-1);
    if(N == 0) return dist;
    queue<int> Q;
    for(int start : starts){
        assert(0 <= start && start < N);
        if(dist[start] != -1) continue;
        dist[start] = 0;
        Q.push(start);
    }
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

// 長方形盤面の4近傍BFS。壁/範囲外の始点なら全マス-1。O(HW)。
vector<vector<int>> grid_bfs(const vector<string>& G,pair<int,int> start,char wall = '#'){
    int H = static_cast<int>(G.size());
    int W = 0;
    if(H > 0) W = static_cast<int>(G[0].size());
    for(const auto& row : G) assert(static_cast<int>(row.size()) == W);
    vector<vector<int>> dist(H,vector<int>(W,-1));
    int sy = start.first;
    int sx = start.second;
    if(sy < 0 || sy >= H || sx < 0 || sx >= W || G[sy][sx] == wall) return dist;
    const int dy[] = {1,0,-1,0},dx[] = {0,1,0,-1};
    queue<pair<int,int>> Q;
    dist[sy][sx] = 0;
    Q.push(start);
    while(!Q.empty()){
        int y = Q.front().first;
        int x = Q.front().second;
        Q.pop();
        for(int k = 0;k < 4;k++){
            int ny = y + dy[k],nx = x + dx[k];
            if(ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
            if(G[ny][nx] == wall || dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            Q.push({ny,nx});
        }
    }
    return dist;
}

// グリッドの多始点BFS。各マスまでの最も近い始点からの距離。到達不能=-1。
// 壁/範囲外の始点は無視し、重複する始点は一度だけ追加する。
// 有効な始点がなければ全マス-1。始点数KとしてO(HW+K)。
vector<vector<int>> grid_multi_source_bfs(const vector<string>& G,const vector<pair<int,int>>& starts,char wall = '#'){
    int H = static_cast<int>(G.size());
    int W = 0;
    if(H > 0) W = static_cast<int>(G[0].size());
    for(const auto& row : G) assert(static_cast<int>(row.size()) == W);
    vector<vector<int>> dist(H,vector<int>(W,-1));
    const int dy[] = {1,0,-1,0},dx[] = {0,1,0,-1};
    queue<pair<int,int>> Q;
    for(auto start : starts){
        int y = start.first;
        int x = start.second;
        if(y < 0 || y >= H || x < 0 || x >= W) continue;
        if(G[y][x] == wall || dist[y][x] != -1) continue;
        dist[y][x] = 0;
        Q.push(start);
    }
    while(!Q.empty()){
        int y = Q.front().first;
        int x = Q.front().second;
        Q.pop();
        for(int k = 0;k < 4;k++){
            int ny = y + dy[k],nx = x + dx[k];
            if(ny < 0 || ny >= H || nx < 0 || nx >= W) continue;
            if(G[ny][nx] == wall || dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            Q.push({ny,nx});
        }
    }
    return dist;
}
