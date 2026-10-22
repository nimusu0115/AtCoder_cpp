#include <bits/stdc++.h>
using namespace std;

// 無重みグラフの最短辺数。到達不能=-1。O(V+E)、空グラフは空配列。
vector<int> bfs(const vector<vector<int>>& g, int start) {
    int n = static_cast<int>(g.size());
    vector<int> dist(n, -1);
    if(n == 0) return dist;
    assert(0 <= start && start < n);
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while(!q.empty()) {
        int v = q.front(); q.pop();
        for(int to : g[v]) if(dist[to] == -1) {
            dist[to] = dist[v] + 1;
            q.push(to);
        }
    }
    return dist;
}

// 長方形盤面の4近傍BFS。壁/範囲外の始点なら全マス-1。O(HW)。
vector<vector<int>> grid_bfs(const vector<string>& grid, pair<int,int> start, char wall = '#') {
    int h = static_cast<int>(grid.size());
    int w = h ? static_cast<int>(grid[0].size()) : 0;
    for(const auto& row : grid) assert(static_cast<int>(row.size()) == w);
    vector<vector<int>> dist(h, vector<int>(w, -1));
    auto [sy, sx] = start;
    if(sy < 0 || sy >= h || sx < 0 || sx >= w || grid[sy][sx] == wall) return dist;
    const int dy[] = {1,0,-1,0}, dx[] = {0,1,0,-1};
    queue<pair<int,int>> q;
    dist[sy][sx] = 0;
    q.push(start);
    while(!q.empty()) {
        auto [y,x] = q.front(); q.pop();
        for(int k = 0; k < 4; ++k) {
            int ny = y + dy[k], nx = x + dx[k];
            if(ny < 0 || ny >= h || nx < 0 || nx >= w) continue;
            if(grid[ny][nx] == wall || dist[ny][nx] != -1) continue;
            dist[ny][nx] = dist[y][x] + 1;
            q.push({ny,nx});
        }
    }
    return dist;
}
