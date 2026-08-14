#include<bits/stdc++.h>
using namespace std;
#define ll long long

// 1点加算と区間和を O(log N) で処理するFenwick Tree（BIT）。
// 外部から指定する添字は0-indexed。
struct FenwickTree{
    int N;
    vector<ll> bit;

    // 要素数 n、全要素0で初期化する。
    explicit FenwickTree(int n) : N(n), bit(n + 1, 0) {}

    // a[index] に value を加える。
    void add(int index,ll value){
        for(int i = index + 1;i <= N;i += i & -i){
            bit[i] += value;
        }
    }

    // 半開区間 [0,r) の総和を返す。
    ll sum(int r) const{
        ll res = 0;
        for(int i = r;i > 0;i -= i & -i){
            res += bit[i];
        }
        return res;
    }

    // 半開区間 [l,r) の総和を返す。
    ll sum(int l,int r) const{
        return sum(r) - sum(l);
    }

    // sum(0,index+1) >= value となる最小の index を返す。
    // 全要素が非負であることが前提。全体の和より value が大きければ N を返す。
    int lower_bound(ll value) const{
        if(value <= 0) return 0;

        int index = 0;
        int step = 1;
        while(step < N) step <<= 1;

        for(;step > 0;step >>= 1){
            int next = index + step;
            if(next <= N && bit[next] < value){
                index = next;
                value -= bit[next];
            }
        }
        return index;
    }
};
