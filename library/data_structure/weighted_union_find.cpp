#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// potential[y]-potential[x]=wという制約を管理する。ならしO(alpha(N))。
// 各保存差分・問い合わせ結果はlong longに収まること。中間計算は128bit。
struct WeightedUnionFind{
    vector<int> parent; // 根では負の集合サイズ
    vector<ll> delta; // 自分のpotential - 親のpotential
    explicit WeightedUnionFind(int N) : parent(N,-1),delta(N,0){}
    static ll narrow(__int128 value){
        assert(LLONG_MIN <= value && value <= LLONG_MAX);
        return static_cast<ll>(value);
    }
    int root(int x){
        if(parent[x] < 0) return x;
        int p = parent[x];
        int r = root(p); // サイズ併合により再帰深さO(log N)。
        delta[x] = narrow(static_cast<__int128>(delta[x]) + delta[p]);
        return parent[x] = r;
    }
    ll weight(int x){
        root(x);
        return delta[x];
    }
    bool same(int x,int y){
        return root(x) == root(y);
    }
    int size(int x){
        return -parent[root(x)];
    }
    // 非連結ならnullopt、連結ならpotential[y]-potential[x]。
    optional<ll> diff(int x,int y){
        if(!same(x,y)) return nullopt;
        return narrow(static_cast<__int128>(delta[y]) - delta[x]);
    }
    // 制約を追加。既存制約と矛盾するとfalse（制約内容は変更しない）。
    bool unite(int x,int y,ll w){
        int rx = root(x);
        int ry = root(y);
        __int128 difference = static_cast<__int128>(w) + delta[x] - delta[y];
        if(rx == ry) return difference == 0;
        if(parent[rx] > parent[ry]){
            swap(rx,ry);
            difference = -difference;
        }
        ll stored = narrow(difference);
        parent[rx] += parent[ry];
        parent[ry] = rx;
        delta[ry] = stored;
        return true;
    }
};
