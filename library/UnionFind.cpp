#include<bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i = 0;i < n;i++)

// 素集合データ構造。経路圧縮とunion by sizeにより連結成分を管理する。
struct UnionFind{

    vector<int> par;
    vector<int> siz;

    // 0～n-1 をそれぞれ独立した集合として初期化する。
    explicit UnionFind(int n) : par(n), siz(n, 1) {
        iota(par.begin(), par.end(), 0);
    }

    // x が属する集合の代表元を返す。探索中に経路圧縮も行う。
    int root(int x){
        if(par[x] == x) return x;
        return par[x] = root(par[x]);
    }

    // x と y が属する集合を併合する。
    void unite(int x,int y){
        int rx = root(x);
        int ry = root(y);
        if(rx == ry) return;
        if(siz[rx] < siz[ry]) swap(rx, ry);
        par[ry] = rx;
        siz[rx] += siz[ry];
    }

    // x と y が同じ集合に属していれば true を返す。
    bool same(int x,int y){
        int rx = root(x);
        int ry = root(y);
        return rx == ry;
    }

    // x が属する集合の要素数を返す。
    int size(int x){
        return siz[root(x)];
    }

};
