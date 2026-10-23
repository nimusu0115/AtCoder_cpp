#include<bits/stdc++.h>
using namespace std;
using ll = long long;

//N以下の素数をO(N log log N)で生成する．
//primesには素数が昇順で入る.
vector<int> enumerate_primes(int N) {
    vector<bool> is_prime(N + 1, true);

    if (N >= 0) is_prime[0] = false;
    if (N >= 1) is_prime[1] = false;

    for (int p = 2; 1LL * p * p <= N; p++) {
        if (!is_prime[p]) continue;

        for (ll x = 1LL * p * p; x <= N; x += p) {
            is_prime[x] = false;
        }
    }

    vector<int> primes;
    for (int x = 2; x <= N; x++) {
        if (is_prime[x]) primes.push_back(x);
    }

    return primes;
};


// 2～Nの最小素因数を O(N log log N) で前計算するエラトステネスの篩。
// 素数判定と素因数分解を繰り返し行う場合に使用する。
struct Eratosthenes{
    int N;
    vector<int> min_factor;
    vector<int> primes;

    explicit Eratosthenes(int n) : N(n), min_factor(n + 1,-1){
        for(int p = 2;p <= N;p++){
            if(min_factor[p] != -1) continue;
            min_factor[p] = p;
            primes.push_back(p);

            if(1LL * p * p > N) continue;
            for(ll multiple = 1LL * p * p;multiple <= N;multiple += p){
                if(min_factor[multiple] == -1) min_factor[multiple] = p;
            }
        }
    }

    // xが素数なら true を返す。前提: 0 <= x <= N。
    bool is_prime(int x) const{
        assert(0 <= x && x <= N);
        return x >= 2 && min_factor[x] == x;
    }

    // xを素因数分解し、{素因数,指数}の配列を昇順で返す。
    // 前提: 1 <= x <= N。
    vector<pair<int,int>> factorize(int x) const{
        assert(1 <= x && x <= N);
        vector<pair<int,int>> res;
        while(x > 1){
            int p = min_factor[x];
            int count = 0;
            while(x % p == 0){
                x /= p;
                count++;
            }
            res.push_back({p,count});
        }
        return res;
    }

    // xの正の約数を昇順ですべて返す。前提: 1 <= x <= N。
    vector<int> divisors(int x) const{
        vector<int> res = {1};
        for(auto [p,count] : factorize(x)){
            int current_size = static_cast<int>(res.size());
            int value = 1;
            for(int e = 1;e <= count;e++){
                value *= p;
                for(int i = 0;i < current_size;i++) res.push_back(res[i] * value);
            }
        }
        sort(res.begin(),res.end());
        return res;
    }
};
