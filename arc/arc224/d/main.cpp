#include<bits/stdc++.h>
using namespace std;
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
ll keta(ll x,int a){
    ll k = 0;
    while(x > 0){
        x /= a;
        k++;
    }
    return k;
}

ll pw(ll a,ll b){
    ll res = 1;
    while(b > 0){
        res *= a;
        b--;
    }
    return res;
}
// AtCoder の modint を使う
#include <atcoder/modint>
using mint = atcoder::modint998244353;

const int MAX = 510000;
mint fac[MAX], finv[MAX], inv[MAX];

// テーブルを作る前処理
void COMinit() {
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

// 二項係数計算
mint COM(int n, int k){
    if (n < k) return 0;
    if (n < 0 || k < 0) return 0;
    return fac[n] * finv[k] * finv[n - k];
}

int main() {
    COMinit();
    int T;
    cin >> T;
    while(T > 0){
        T--;

        ll N,K;
        cin >> N >> K;
        K--;

        if(N <= 20){
            if(pw(2,N) < K){
                cout << -1 << endl;
                continue;
            }
        } 

        ll cost = 1;
        ll multi = 1;
        ll z = COM(N,multi).val();
        ll ans = 0;
        while(K > 0){
            if(K >= pw(10,cost) - pw(10,cost - 1)){
                K -= pw(10,cost) - pw(10,cost - 1);
                ll p = pw(10,cost) - pw(10,cost - 1);

                while(p > 0){
                    
                   if(z <= p){
                        p -= z;
                        ans += multi * cost * z;
                        multi++;
                        z = COM(N,multi).val();
                   } 
                   else{
                        ans += multi * cost * p;
                        z -= p;
                        p = 0;
                    }
                }

                cost++;
            }
            else{
                while(K > 0){
                   if(z <= K){
                        K -= z;
                        ans += multi * cost * z;
                        multi++;
                        z = COM(N,multi).val();
                   } 
                   else{
                    ans += multi * cost * K;
                    K = 0;
                   }
                }
            }
        }

        cout << ans << endl;
    }
}