#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// オフライン区間加算。add O(1)、build O(N)、再度buildしても差分は壊さない。
// 差分を128bitで持ち、各セルの最終値だけlong longに収まることを要求する。
struct Imos{
    vector<__int128> difference;
    explicit Imos(int N) : difference(N + 1){
        assert(N >= 0);
    }
    void add(int l,int r,ll value){
        assert(0 <= l && l <= r && r < static_cast<int>(difference.size()));
        difference[l] += value;
        difference[r] -= value;
    }
    vector<ll> build() const{
        vector<ll> result(difference.size() - 1);
        __int128 current = 0;
        for(int i = 0;i < static_cast<int>(result.size());i++){
            current += difference[i];
            assert(LLONG_MIN <= current && current <= LLONG_MAX);
            result[i] = static_cast<ll>(current);
        }
        return result;
    }
};

// [y1,y2)×[x1,x2)への加算。add O(1)、build O(HW)、空の盤面可。
struct Imos2D{
    int h,w;
    vector<vector<__int128>> difference;
    Imos2D(int height,int width) : h(height),w(width),difference(h + 1,vector<__int128>(w + 1)){
        assert(h >= 0 && w >= 0);
    }
    void add(int y1,int x1,int y2,int x2,ll value){
        assert(0 <= y1 && y1 <= y2 && y2 <= h && 0 <= x1 && x1 <= x2 && x2 <= w);
        difference[y1][x1] += value;
        difference[y2][x1] -= value;
        difference[y1][x2] -= value;
        difference[y2][x2] += value;
    }
    vector<vector<ll>> build() const{
        auto work = difference;
        vector<vector<ll>> result(h,vector<ll>(w));
        for(int y = 0;y < h;y++){
            for(int x = 0;x < w;x++){
                if(y > 0) work[y][x] += work[y - 1][x];
                if(x > 0) work[y][x] += work[y][x - 1];
                if(y > 0 && x > 0) work[y][x] -= work[y - 1][x - 1];
                assert(LLONG_MIN <= work[y][x] && work[y][x] <= LLONG_MAX);
                result[y][x] = static_cast<ll>(work[y][x]);
            }
        }
        return result;
    }
};
