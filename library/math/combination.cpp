#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;

// 素数modのmodint用。0<=n<mod、構築O(n+log mod)、空間O(n)、nCk O(1)。
// dynamic_modintは構築後にmodを変更しない。必要な最大nだけ確保する。
template<class Mint>
struct Combination {
    vector<Mint> fac, finv;
    explicit Combination(int n) {
        assert(0 <= n && n < Mint::mod());
        fac.resize(n+1); finv.resize(n+1);
        fac[0] = 1;
        for(int i = 1; i <= n; ++i) fac[i] = fac[i-1] * i;
        finv[n] = fac[n].inv();
        for(int i = n; i > 0; --i) finv[i-1] = finv[i] * i;
    }
    Mint com(int n, int k) const {
        if(n < 0 || k < 0 || n < k) return 0;
        assert(n < static_cast<int>(fac.size()));
        return fac[n] * finv[k] * finv[n-k];
    }
};
