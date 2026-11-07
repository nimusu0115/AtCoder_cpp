//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i,n) for(ll i = 0;i < n;i++)
#define rrep(i,n) for(ll i = n - 1;i >= 0;i--)
#define onerep(i,n) for(ll i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int keta(ll x,int a){
    assert(x >= 0 && a >= 2);
    if(x == 0) return 1;
    int k = 0;
    while(x > 0){
        x /= a;
        k++;
    }
    return k;
}

ll pw(ll a,ll b){
    assert(b >= 0);
    ll res = 1;
    while(b > 0){
        if(b & 1){
            __int128 value = static_cast<__int128>(res) * a;
            assert(LLONG_MIN <= value && value <= LLONG_MAX);
            res = static_cast<ll>(value);
        }
        b >>= 1;
        if(b){
            __int128 value = static_cast<__int128>(a) * a;
            assert(value <= LLONG_MAX);
            a = static_cast<ll>(value);
        }
    }
    return res;
}

ll solve(ll x){
    int k = keta(x,10);

    vector<vector<vector<ll>>> dp(k,vector<vector<ll>>(2,vector<ll>(10,0)));
    rep(i,10){
        if(i < (x / pw(10,k - 1)) % 10) dp[0][1][i] = 1;
        if(i == (x / pw(10,k - 1)) % 10) dp[0][0][i] = 1;
    }

    rep(i,k - 1){
        rep(smaller,2){
            rep(head,10){

                rep(d,10){
                    if(!smaller && d > (x / pw(10,k - i - 2)) % 10) continue;

                    int ns = smaller || (d < (x / pw(10,k - i - 2)) % 10);
                    int nh;
                    if(head == 0){
                        nh = d;
                    }else{
                        if(d >= head) continue;
                        nh = head;
                    }

                    dp[i + 1][ns][nh] += dp[i][smaller][head];
                }
            }
        }
    }

    ll ans = 0;
    rep(i,10) ans += dp[k - 1][0][i] + dp[k - 1][1][i];
    return ans;
}

int main() {
    ll L,R;
    cin >> L >> R;

    cout << solve(R) - solve(L - 1) << endl;
}