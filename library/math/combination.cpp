#include<bits/stdc++.h>
#include <atcoder/modint>
using namespace std;

// 素数modのmodint用。0<=n<mod、構築O(n+log mod)、空間O(n)、nCk O(1)。
// dynamic_modintは構築後にmodを変更しない。必要な最大nだけ確保する。
template<class Mint>
struct Combination{
    vector<Mint> fac,finv;
    explicit Combination(int N){
        assert(0 <= N && N < Mint::mod());
        fac.resize(N + 1);
        finv.resize(N + 1);
        fac[0] = 1;
        for(int i = 1;i <= N;i++) fac[i] = fac[i - 1] * i;
        finv[N] = fac[N].inv();
        for(int i = N;i > 0;i--) finv[i - 1] = finv[i] * i;
    }
    Mint com(int N,int k) const{
        if(N < 0 || k < 0 || N < k) return 0;
        assert(N < static_cast<int>(fac.size()));
        return fac[N] * finv[k] * finv[N - k];
    }
};
