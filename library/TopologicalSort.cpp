#include<bits/stdc++.h>
using namespace std;

// 有向グラフをKahn法でトポロジカルソートする。計算量は O(N+M)。
// G[from]に辺の行き先を格納する。閉路が存在する場合は空配列を返す。
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
