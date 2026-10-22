// 実行例。提出時はinclude行の代わりに対象.cppを貼り付ける。
#include "../tree/rerooting.cpp"

int main(){
    // 各頂点からの距離の総和（n=3のパス）。
    vector<vector<pair<int,int>>> G = {{{1,0}},{{0,0},{2,1}},{{1,1}}};
    using State = pair<long long,long long>; // {距離和, 頂点数}
    auto ans = rerooting(G,State{0,0},
        [](State a,State b){ return State{a.first + b.first,a.second + b.second}; },
        [](State a,int){ return State{a.first,a.second + 1}; },
        [](State a,int,int,int){ return State{a.first + a.second,a.second}; });
    assert(ans[0].first == 3 && ans[1].first == 2 && ans[2].first == 3);
}
