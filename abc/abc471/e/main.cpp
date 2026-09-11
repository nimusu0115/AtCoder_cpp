#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}
const ll prm = 998244353;
const int MAX = 10'000'010;
// fac[i]=i!, finv[i]=(i!)^{-1}, inv[i]=i^{-1}（mod 998244353）。
mint fac[MAX], finv[MAX], inv[MAX];

// 0～MAX-1 の階乗・逆元・逆階乗を O(MAX) で前計算する。
// comを呼ぶ前に一度だけ実行する。
void cominit() {
    const int MOD = mint::mod();
    fac[0] = fac[1] = 1;
    finv[0] = finv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < MAX; i++){
        fac[i] = fac[i - 1] * i;
        inv[i] = MOD - inv[MOD%i] * (MOD / i);
        finv[i] = finv[i - 1] * inv[i];
    }
}

// 二項係数 nCk を mod 998244353 で返す。範囲外の k に対しては 0 を返す。
// 前提: cominit()が実行済みで、0 <= n < MAX。
mint com(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    assert(n < MAX);
    return fac[n] * finv[k] * finv[n - k];
}

int main() {
    cominit();

    ll N,K;
    cin >> N >> K;
    vector<mint> A(N);
    rep(i,N){
        ll a;
        cin >> a;
        A[i] = a;
    }

    mint sum = 0;
    mint ans = 0;
    rep(i,N) sum += A[i];

    if(K == 1){
        rep(i,N) ans += A[i] * A[i];
        cout << ans.val() << endl;
        return 0;
    }

    rep(i,N){
        ans += A[i] * A[i] * com(N - 1,K - 1);
        ans += A[i] * (sum - A[i]) * com(N - 2,K - 2);
        //cout << ans.val() << endl; 
    }
    cout << ans.val() << endl;
}