// 実行例。提出時はinclude行の代わりに対象.cppを貼り付ける。
#include "../tree/rerooting.cpp"

using ll = long long;
using DistanceState = pair<ll,ll>; // {距離に頂点重みを掛けた総和, 頂点重みの総和}

DistanceState merge_distance(DistanceState a,DistanceState b){
    return {a.first + b.first,a.second + b.second};
}

struct AddDistanceVertex{
    const vector<ll>& vertex_weight;
    DistanceState operator()(DistanceState a,int v) const{
        return {a.first,a.second + vertex_weight[v]};
    }
};

struct LiftDistance{
    const vector<ll>& edge_weight;
    DistanceState operator()(DistanceState a,int from,int to,int id) const{
        (void)from;
        (void)to;
        return {a.first + a.second * edge_weight[id],a.second};
    }
};

int main(){
    // 各頂点からの距離の総和（n=3のパス）。
    vector<vector<pair<int,int>>> G = {{{1,0}},{{0,0},{2,1}},{{1,1}}};
    vector<ll> vertex_weight = {1,1,1},edge_weight = {1,1};
    auto ans = rerooting(G,DistanceState{0,0},merge_distance,
                        AddDistanceVertex{vertex_weight},LiftDistance{edge_weight});
    assert(ans[0].first == 3 && ans[1].first == 2 && ans[2].first == 3);

    // 頂点・辺の重みを変えても、同じDPを使える。
    vertex_weight = {1,2,3};
    edge_weight = {2,4};
    ans = rerooting(G,DistanceState{0,0},merge_distance,
                   AddDistanceVertex{vertex_weight},LiftDistance{edge_weight});
    assert(ans[0] == DistanceState(22,6));
    assert(ans[1] == DistanceState(14,6));
    assert(ans[2] == DistanceState(14,6));
    auto other_root = rerooting(G,DistanceState{0,0},merge_distance,
                               AddDistanceVertex{vertex_weight},LiftDistance{edge_weight},2);
    assert(ans == other_root);

    vector<vector<pair<int,int>>> single(1);
    vector<ll> single_weight = {5},no_edges;
    auto single_ans = rerooting(single,DistanceState{0,0},merge_distance,
                               AddDistanceVertex{single_weight},LiftDistance{no_edges});
    assert(single_ans[0] == DistanceState(0,5));
}
