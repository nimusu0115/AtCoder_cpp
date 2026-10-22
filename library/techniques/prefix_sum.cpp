#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 累積和。各保存値・返り値がlong longに収まること。空配列可。
// 構築O(N)、半開区間和O(1)。
struct PrefixSum{
    vector<ll> prefix;
    explicit PrefixSum(const vector<ll>& values) : prefix(values.size() + 1){
        for(int i = 0;i < static_cast<int>(values.size());i++){
            __int128 x = static_cast<__int128>(prefix[i]) + values[i];
            assert(LLONG_MIN <= x && x <= LLONG_MAX);
            prefix[i + 1] = static_cast<ll>(x);
        }
    }
    ll sum(int l,int r) const{
        assert(0 <= l && l <= r && r < static_cast<int>(prefix.size()));
        __int128 x = static_cast<__int128>(prefix[r]) - prefix[l];
        assert(LLONG_MIN <= x && x <= LLONG_MAX);
        return static_cast<ll>(x);
    }
};

// 長方形配列の2D累積和。構築O(HW)、[y1,y2)×[x1,x2)の和O(1)。
struct PrefixSum2D{
    int h,w;
    vector<vector<ll>> prefix;
    explicit PrefixSum2D(const vector<vector<ll>>& a){
        h = static_cast<int>(a.size());
        w = 0;
        if(h > 0) w = static_cast<int>(a[0].size());
        prefix.assign(h + 1,vector<ll>(w + 1));
        for(int y = 0;y < h;y++){
            assert(static_cast<int>(a[y].size()) == w);
            for(int x = 0;x < w;x++){
                __int128 v = static_cast<__int128>(a[y][x]) + prefix[y][x + 1] + prefix[y + 1][x] - prefix[y][x];
                assert(LLONG_MIN <= v && v <= LLONG_MAX);
                prefix[y + 1][x + 1] = static_cast<ll>(v);
            }
        }
    }
    ll sum(int y1,int x1,int y2,int x2) const{
        assert(0 <= y1 && y1 <= y2 && y2 <= h && 0 <= x1 && x1 <= x2 && x2 <= w);
        __int128 v = static_cast<__int128>(prefix[y2][x2]) - prefix[y1][x2] - prefix[y2][x1] + prefix[y1][x1];
        assert(LLONG_MIN <= v && v <= LLONG_MAX);
        return static_cast<ll>(v);
    }
};
