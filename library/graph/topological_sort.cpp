#include <bits/stdc++.h>
using namespace std;

// 閉路があれば空配列。空グラフも空配列。既定は辞書順最小、O(E+V log V)。
// lexicographical=falseならqueueを使いO(V+E)。入力は有向グラフ。
vector<int> topological_sort(const vector<vector<int>>& g, bool lexicographical = true) {
    int n = static_cast<int>(g.size());
    vector<int> indegree(n), order;
    for(const auto& row : g) for(int to : row) ++indegree[to];
    priority_queue<int,vector<int>,greater<int>> heap;
    queue<int> fifo;
    auto push = [&](int v) { if(lexicographical) heap.push(v); else fifo.push(v); };
    for(int v = 0; v < n; ++v) if(indegree[v] == 0) push(v);
    while(lexicographical ? !heap.empty() : !fifo.empty()) {
        int v;
        if(lexicographical) { v = heap.top(); heap.pop(); }
        else { v = fifo.front(); fifo.pop(); }
        order.push_back(v);
        for(int to : g[v]) if(--indegree[to] == 0) push(to);
    }
    if(static_cast<int>(order.size()) != n) return {};
    return order;
}
