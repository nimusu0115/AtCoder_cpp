#include<bits/stdc++.h>
#include <atcoder/modint>
using namespace std;

// 問題固有の桁DP例（汎用DPではない）。1..Sで次の条件をちょうど1つ満たす数。
// 使用数字3種類 / 桁和が3の倍数 / 数字3を含む。先頭0は使用数字に含めない。
// O(|S|*2*3*1024*10)、空間O(2*3*1024)。空文字は0、十進数字のみ。
atcoder::modint998244353 count_digit_conditions(const string& S){
    using mint = atcoder::modint998244353;
    // dp[上限S未満か][桁和 mod 3][使用数字の集合]。直前の桁の状態だけ持つ。
    vector<vector<vector<mint>>> dp(2,vector<vector<mint>>(3,vector<mint>(1<<10)));
    dp[0][0][0] = 1;

    for(char c : S){
        assert('0' <= c && c <= '9');
        vector<vector<vector<mint>>> next(2,vector<vector<mint>>(3,vector<mint>(1<<10)));
        for(int smaller = 0;smaller < 2;smaller++){
            for(int mod = 0;mod < 3;mod++){
                for(int bit = 0;bit < (1<<10);bit++){
                    mint ways = dp[smaller][mod][bit];
                    if(ways == mint(0)) continue;

                    int limit = 9;
                    if(smaller == 0) limit = c - '0';
                    for(int p = 0;p <= limit;p++){
                        int next_smaller = smaller | (p < limit);
                        int bitnext = bit | (1<<p);
                        if(bit == 0 && p == 0) bitnext = 0;
                        next[next_smaller][(mod + p) % 3][bitnext] += ways;
                    }
                }
            }
        }
        dp.swap(next);
    }

    mint ans = 0;
    for(int smaller = 0;smaller < 2;smaller++){
        for(int mod = 0;mod < 3;mod++){
            for(int bit = 1;bit < (1<<10);bit++){
                int count = __builtin_popcount(static_cast<unsigned>(bit));
                int cnt = 0;
                if(count == 3) cnt++;
                if(mod == 0) cnt++;
                if((bit>>3) & 1) cnt++;
                if(cnt == 1) ans += dp[smaller][mod][bit];
            }
        }
    }
    return ans;
}
