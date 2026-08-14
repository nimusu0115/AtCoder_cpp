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

mint dp[505][2][3][1<<10];

int main() {
    string S;
    cin >> S;

    int N = S.size();


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

                        //leading-zero
                        if(bit == 0){
                            if(p == 0) dp[i + 1][next_smaller][0][0] += dp[i][smaller][mod][bit];
                            else dp[i + 1][next_smaller][p % 3][bitnext] += dp[i][smaller][mod][bit];
                        }

                        //normal process
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
                //except zero
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