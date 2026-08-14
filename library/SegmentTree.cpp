#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll SEG_INF = 1LL<<60;

// 1点更新と区間最小値を O(log N) で処理するセグメント木。
// 外部から指定する添字は0-indexed、区間は半開区間 [l,r) とする。
struct SegmentTree{
    int size;
    vector<ll> tree;

    // 要素数 n、全要素 SEG_INF で初期化する。
    explicit SegmentTree(int n){
        size = 1;
        while(size < n) size *= 2;
        tree.assign(size * 2,SEG_INF);
    }

    // 配列 values の内容で構築する。計算量は O(N)。
    explicit SegmentTree(const vector<ll>& values) : SegmentTree(static_cast<int>(values.size())){
        for(int i = 0;i < static_cast<int>(values.size());i++) tree[size + i] = values[i];
        for(int i = size - 1;i >= 1;i--) tree[i] = min(tree[i * 2],tree[i * 2 + 1]);
    }

    // a[index] を value に変更する。
    void update(int index,ll value){
        int pos = index + size;
        tree[pos] = value;
        while(pos > 1){
            pos /= 2;
            tree[pos] = min(tree[pos * 2],tree[pos * 2 + 1]);
        }
    }

    // 半開区間 [l,r) に含まれる要素の最小値を返す。
    ll query(int l,int r) const{
        ll res = SEG_INF;
        l += size;
        r += size;

        while(l < r){
            if(l & 1) res = min(res,tree[l++]);
            if(r & 1) res = min(res,tree[--r]);
            l /= 2;
            r /= 2;
        }
        return res;
    }

    // a[index] の現在値を返す。
    ll get(int index) const{
        return tree[size + index];
    }
};
