#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;

// 問題固有の桁DP例（汎用DPではない）。1..Sで次の条件をちょうど1つ満たす数。
// 使用数字3種類 / 桁和が3の倍数 / 数字3を含む。先頭0は使用数字に含めない。
// O(|S|*2*3*1024*10)、空間O(2*3*1024)。空文字は0、十進数字のみ。
atcoder::modint998244353 count_digit_conditions(const string& s) {
    using Mint = atcoder::modint998244353;
    vector<Mint> dp(2*3*1024), next(dp.size());
    auto index = [](int small, int mod, int mask) { return (small*3+mod)*1024+mask; };
    dp[0] = 1;
    for(char c : s) {
        assert('0' <= c && c <= '9');
        fill(next.begin(),next.end(),Mint(0));
        for(int small = 0; small < 2; ++small) for(int mod = 0; mod < 3; ++mod) {
            for(int mask = 0; mask < 1024; ++mask) {
                Mint ways = dp[index(small,mod,mask)];
                if(ways == Mint(0)) continue;
                int limit = small ? 9 : c-'0';
                for(int d = 0; d <= limit; ++d) {
                    int nm = (mask == 0 && d == 0) ? 0 : mask | (1<<d);
                    next[index(small || d < c-'0', (mod+d)%3, nm)] += ways;
                }
            }
        }
        dp.swap(next);
    }
    Mint answer = 0;
    for(int small = 0; small < 2; ++small) for(int mod = 0; mod < 3; ++mod) {
        for(int mask = 1; mask < 1024; ++mask) {
            int conditions = (__builtin_popcount(static_cast<unsigned>(mask)) == 3)
                           + (mod == 0) + ((mask>>3)&1);
            if(conditions == 1) answer += dp[index(small,mod,mask)];
        }
    }
    return answer;
}
