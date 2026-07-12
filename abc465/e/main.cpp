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
ll prm = 998244353;

int main() {
    string S;
    cin >> S;

    int N = S.size();

    ll dp[N][2][3][1<<10] = {0};

    onerep(p,S[0] - '0'){
        if(p == S[0] - '0') dp[0][1][p % 3][1<<p] = 1;
        else dp[0][0][p % 3][1<<p] = 1;
    }
    
    rep(i,N - 1){
        rep(j,2){
            rep(k,3){
                rep(bit,1<<10){
                    if(j == 1){
                        rep(p,S[i] - '0'){
                            int bitnext = bit | (1<<p);
                            dp[i + 1][0][(k + p) % 3][bitnext] += dp[i][j][k][bit] % prm;
                        }
                        dp[i + 1][1][(k + S[i] - '0') % 3][bit | (1<<S[i] - '0')] += dp[i][j][k][bit] % prm;
                        continue;
                    }

                    set<int> s = {};
                    rep(p,10) if(((bit>>i) & 1) == 1) s.insert(p);
                    if(s.size() == 1 && s.count(0)){
                        onerep(p,9){
                            int bitnext = bit | (1<<p);
                            dp[i + 1][0][(k + p) % 3][bitnext] += dp[i][j][k][bit] % prm;
                        }
                        continue;
                    }

                    rep(p,10){
                        int bitnext = bit | (1<<p);
                        dp[i + 1][0][(k + p) % 3][bitnext] += dp[i][j][k][bit] % prm;
                    }
                }
            }
        }
    }

    ll ans = 0;
    rep(j,2){
        rep(k,2){
            rep(l,3){
                rep(bit,1<<10){
                    set<int> s = {};
                    rep(p,10) if(((bit>>i) & 1) == 1) s.insert(p);

                    int a = 0;
                    if()
                }
            }
        }
    }
}