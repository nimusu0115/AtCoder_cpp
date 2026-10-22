#include<bits/stdc++.h>
using namespace std;

// 閉路があれば空配列。空グラフも空配列。既定は辞書順最小、O(E+V log V)。
// lexicographical=falseならqueueを使いO(V+E)。入力は有向グラフ。
vector<int> topological_sort(const vector<vector<int>>& G,bool lexicographical = true){
    int N = static_cast<int>(G.size());
    vector<int> indegree(N),order;
    for(int from = 0;from < N;from++){
        for(int to : G[from]) indegree[to]++;
    }
    priority_queue<int,vector<int>,greater<int>> Q;
    queue<int> normal_Q;
    for(int pos = 0;pos < N;pos++){
        if(indegree[pos] != 0) continue;
        if(lexicographical) Q.push(pos);
        else normal_Q.push(pos);
    }
    while(!Q.empty() || !normal_Q.empty()){
        int pos;
        if(lexicographical){
            pos = Q.top();
            Q.pop();
        }
        else{
            pos = normal_Q.front();
            normal_Q.pop();
        }
        order.push_back(pos);
        for(int to : G[pos]){
            indegree[to]--;
            if(indegree[to] != 0) continue;
            if(lexicographical) Q.push(to);
            else normal_Q.push(to);
        }
    }
    if(static_cast<int>(order.size()) != N) return {};
    return order;
}
