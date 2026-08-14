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

int main() {
    int H,W;
    cin >> H >> W;
    vector<string> S(H);
    rep(i,H) cin >> S[i];

    int ans = 0;
    rep(i,H){
        rep(j,W){
            rep(k,H){
                rep(l,W){
                    if(i > k || j > l) continue;
                    bool flg = true;
                    for(int p = i;p <= k;p++){
                        for(int q = j;q <= l;q++){
                            if(S[p][q] != S[i + k - p][j + l - q]) flg = false;
                        }
                    }
                    if(flg) ans++;
                }
            }
        }
    }

    cout << ans << endl;
}