#include "../graph/bfs.cpp"

mt19937 rng(20261023);

void graph_tests(){
    assert(multi_source_bfs({},{}).empty());
    assert((multi_source_bfs({{}},{}) == vector<int>{-1}));
    assert((multi_source_bfs({{}},{0,0}) == vector<int>{0}));
    vector<vector<int>> G = {{1},{0,2},{1},{}};
    assert((multi_source_bfs(G,{0,2,0}) == vector<int>{0,1,0,-1}));
    assert((multi_source_bfs({{1},{}},{1}) == vector<int>{-1,0}));

    // 全点間最短距離から始点ごとの最小値を取り、独立した期待値を作る。
    for(int trial = 0;trial < 300;trial++){
        int N = 1 + rng() % 24;
        vector<vector<int>> G(N);
        vector<vector<int>> shortest(N,vector<int>(N,10000));
        for(int v = 0;v < N;v++) shortest[v][v] = 0;
        for(int v = 0;v < N;v++){
            for(int to = 0;to < N;to++){
                if(rng() % 5 != 0) continue;
                G[v].push_back(to);
                shortest[v][to] = min(shortest[v][to],1);
                if(trial % 2 == 0){
                    G[to].push_back(v);
                    shortest[to][v] = min(shortest[to][v],1);
                }
            }
        }
        for(int k = 0;k < N;k++){
            for(int v = 0;v < N;v++){
                for(int to = 0;to < N;to++){
                    shortest[v][to] = min(shortest[v][to],shortest[v][k] + shortest[k][to]);
                }
            }
        }
        int K = rng() % (2 * N + 1);
        vector<int> starts(K);
        for(int& start : starts) start = rng() % N;
        vector<int> expected(N,-1);
        for(int v = 0;v < N;v++){
            int best = 10000;
            for(int start : starts) best = min(best,shortest[start][v]);
            if(best < 10000) expected[v] = best;
        }
        assert(multi_source_bfs(G,starts) == expected);
        assert(multi_source_bfs(G,starts) == expected); // 同一入力を再利用可能。
        int start = rng() % N;
        assert(multi_source_bfs(G,{start}) == bfs(G,start));
        vector<int> all(N);
        iota(all.begin(),all.end(),0);
        assert(multi_source_bfs(G,all) == vector<int>(N,0));
    }

    int N = 200000;
    vector<vector<int>> path(N);
    for(int v = 1;v < N;v++){
        path[v - 1].push_back(v);
        path[v].push_back(v - 1);
    }
    vector<int> starts(N,0); // 大量の重複も一度だけキューに入れる。
    starts.push_back(N - 1);
    auto dist = multi_source_bfs(path,starts);
    for(int v = 0;v < N;v++) assert(dist[v] == min(v,N - 1 - v));
}

void grid_tests(){
    assert(grid_multi_source_bfs({},{}).empty());
    assert(grid_multi_source_bfs({},{{0,0}}).empty());
    assert(grid_multi_source_bfs({""},{{0,0}})[0].empty());
    assert(grid_multi_source_bfs({"."},{})[0][0] == -1);
    assert(grid_multi_source_bfs({"#"},{{0,0}})[0][0] == -1);
    assert(grid_multi_source_bfs({"."},{{0,0},{0,0}})[0][0] == 0);
    assert((grid_multi_source_bfs({".*."},{{0,0},{0,2}},'*')[0] == vector<int>{0,-1,0}));

    // 各始点からの単始点BFSの最小値と比較。無効始点・壁・重複も含む。
    for(int trial = 0;trial < 200;trial++){
        int H = rng() % 9;
        int W = rng() % 9;
        char wall = '#';
        if(trial % 2 == 0) wall = '*';
        vector<string> G(H,string(W,'.'));
        for(auto& row : G){
            for(char& c : row){
                if(rng() % 3 == 0) c = wall;
            }
        }
        int K = rng() % 20;
        vector<pair<int,int>> starts;
        for(int i = 0;i < K;i++){
            int y = static_cast<int>(rng() % (H + 2)) - 1;
            int x = static_cast<int>(rng() % (W + 2)) - 1;
            starts.push_back({y,x});
            if(i % 3 == 0) starts.push_back({y,x});
        }
        vector<vector<int>> expected(H,vector<int>(W,-1));
        for(auto start : starts){
            auto dist = grid_bfs(G,start,wall);
            for(int y = 0;y < H;y++){
                for(int x = 0;x < W;x++){
                    if(dist[y][x] == -1) continue;
                    if(expected[y][x] == -1 || dist[y][x] < expected[y][x]) expected[y][x] = dist[y][x];
                }
            }
        }
        assert(grid_multi_source_bfs(G,starts,wall) == expected);
        assert(grid_multi_source_bfs(G,starts,wall) == expected);
    }
}

int main(){
    graph_tests();
    grid_tests();
    cout << "multi-source BFS: 300 graphs, 200 grids, edge cases and 200000-vertex path passed" << endl;
}
