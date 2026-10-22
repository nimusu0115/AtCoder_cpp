// 元のSCC使用例: 相互に到達可能な異なる頂点の組数。
// 提出時はinclude行の代わりに対象.cppを貼り付ける。
#include "../graph/scc.cpp"

int main() {
    int n,m;
    if(!(cin>>n>>m)) return 0;
    vector<vector<int>> g(n);
    for(int i=0; i<m; ++i) { int a,b; cin>>a>>b; g[a-1].push_back(b-1); }
    auto id=scc(g); vector<long long> count(n);
    for(int x : id) ++count[x];
    long long answer=0;
    for(long long size : count) answer+=size*(size-1)/2;
    cout<<answer<<'\n';
}
