// 元のSCC使用例: 相互に到達可能な異なる頂点の組数。
// 提出時はinclude行の代わりに対象.cppを貼り付ける。
#include "../graph/scc.cpp"

int main(){
    int N,M;
    if(!(cin >> N >> M)) return 0;
    vector<vector<int>> G(N);
    for(int i = 0;i < M;i++){
        int a,b;
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
    }
    auto id = scc(G);
    vector<long long> count(N);
    for(int x : id) count[x]++;
    long long ans = 0;
    for(long long size : count) ans += size * (size - 1) / 2;
    cout << ans << endl;
}
