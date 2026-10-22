// 実行例。提出時はinclude行の代わりに対象.cppを貼り付ける。
#include "../tree/rerooting.cpp"

int main() {
    // 各頂点からの距離の総和（n=3のパス）。
    vector<vector<pair<int,int>>> g = {{{1,0}}, {{0,0},{2,1}}, {{1,1}}};
    using State = pair<long long,long long>; // {距離和, 頂点数}
    auto answer = rerooting(g,State{0,0},
        [](State a,State b) { return State{a.first+b.first,a.second+b.second}; },
        [](State a,int) { return State{a.first,a.second+1}; },
        [](State a,int,int,int) { return State{a.first+a.second,a.second}; });
    assert(answer[0].first==3 && answer[1].first==2 && answer[2].first==3);
}
