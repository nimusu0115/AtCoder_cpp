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
// a を現在値と b の大きい方／小さい方に更新する。
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

// dp[桁数][上限S未満か][各桁の和 mod 3][使用した数字の集合]。
// 各状態に該当する整数の個数を mod 998244353 で保持する。
mint dp[505][2][3][1<<10];

// 1～Sの整数のうち、次の3条件をちょうど1つ満たすものを数える。
// 「異なる数字を3種類使う」「各桁の和が3の倍数」「数字3を使う」。
int main() {
    string S;
    cin >> S;

    assert(S.size() < 505);
    int N = static_cast<int>(S.size());


    dp[0][0][0][0] = 1;
    
    rep(i,N){
        rep(smaller,2){
            rep(mod,3){
                rep(bit,1<<10){

                    int limit;
                    if(smaller == 0) limit = S[i] - '0';
                    else limit = 9;

                    rep(p,limit + 1){
                        int next_smaller = smaller | (p < limit);
                        int bitnext = bit | (1<<p);

                        // まだ有効数字を置いていない間は、0を使用数字に含めない。
                        if(bit == 0){
                            if(p == 0) dp[i + 1][next_smaller][0][0] += dp[i][smaller][mod][bit];
                            else dp[i + 1][next_smaller][p % 3][bitnext] += dp[i][smaller][mod][bit];
                        }

                        // 有効数字の開始後は、使用数字と各桁の和を更新する。
                        else dp[i + 1][next_smaller][(mod + p) % 3][bitnext] += dp[i][smaller][mod][bit];
                    }

                }
            }
        }
    }

    mint ans = 0;
    rep(smaller,2){
        rep(mod,3){
            rep(bit,1<<10){
                // 何も有効数字を置かなかった状態（整数0）は数えない。
                if(bit == 0) continue;

                int count = 0;
                rep(p,10) if(((bit>>p) & 1) == 1) count++;

                int cnt = 0;
                if(count == 3) cnt++;
                if(mod == 0) cnt++;
                if(((bit>>3) & 1) == 1) cnt++;

                if(cnt == 1) ans += dp[N][smaller][mod][bit];
            }
        }
    }

    cout << ans.val() << endl;
}
