#include <bits/stdc++.h>
using namespace std;

// 全方位木DP。g[v]は{隣接頂点, 辺ID}。同じ無向辺の両側に同じIDを使う。
// merge(a,b): 結合則を満たす演算、identity: 単位元。可換性は不要。
// add_vertex(隣接側からの集約,v): 頂点vを追加したDP値。
// lift(DP,from,to,id): 辺from->toを通してto側へ渡す寄与。
// 戻り値[v]=vを根としたDP。隣接リスト順を維持する。
// 連結無向木（空木可）。各操作O(1)ならO(N)時間・空間、再帰なし。
template<class T, class Merge, class AddVertex, class Lift>
vector<T> rerooting(const vector<vector<pair<int,int>>>& g, T identity,
                    Merge merge, AddVertex add_vertex, Lift lift, int root = 0) {
    int n = static_cast<int>(g.size());
    if(n == 0) return {};
    assert(0 <= root && root < n);
    vector<int> parent(n,-1), order = {root};
    parent[root] = root;
    for(int i = 0; i < static_cast<int>(order.size()); ++i) {
        int v = order[i];
        for(auto [to,id] : g[v]) {
            (void)id;
            if(parent[to] != -1) continue;
            parent[to] = v; order.push_back(to);
        }
    }
    assert(static_cast<int>(order.size()) == n);
    vector<T> down(n,identity), up(n,identity), answer(n,identity);
    for(int i = n-1; i >= 0; --i) {
        int v = order[i]; T aggregate = identity;
        for(auto [to,id] : g[v]) if(to != parent[v]) {
            aggregate = merge(aggregate,lift(down[to],to,v,id));
        }
        down[v] = add_vertex(aggregate,v);
    }
    for(int v : order) {
        int degree = static_cast<int>(g[v].size());
        vector<T> contribution(degree,identity), prefix(degree+1,identity);
        for(int i = 0; i < degree; ++i) {
            auto [to,id] = g[v][i];
            contribution[i] = to == parent[v] ? up[v] : lift(down[to],to,v,id);
            prefix[i+1] = merge(prefix[i],contribution[i]);
        }
        answer[v] = add_vertex(prefix[degree],v);
        T suffix = identity;
        for(int i = degree-1; i >= 0; --i) {
            auto [to,id] = g[v][i];
            if(to != parent[v]) {
                T without = merge(prefix[i],suffix);
                up[to] = lift(add_vertex(without,v),v,to,id);
            }
            suffix = merge(contribution[i],suffix);
        }
    }
    return answer;
}
