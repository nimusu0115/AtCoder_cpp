//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

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

int main() {
    int N,M;
    cin >> N >> M;
    vector<string> S(N),T(M);
    rep(i,N) cin >> S[i];
    rep(i,M) cin >> T[i];

    vector<int> ans(N,0);
    rep(i,M){
        bool flg = false;
        rep(j,N) if(T[i] == S[j]) ans[j]++,flg = true;

        if(flg) continue;
        vector<int> cnt(N,0);
        rep(k,T[i].size()){
            rep(l,26){
                char c = 'a' + l;
                string t = T[i];
                if(t[k] == c) continue;
                else{
                    t[k] = c;
                    rep(p,N) if(t == S[p]) cnt[p]++;
                }
            }
        }

        int m = 0;
        rep(q,N) m += cnt[q];
        if(m == 1){
            rep(x,N) if(cnt[x] == 1) ans[x]++;
        }
    }

    rep(i,N) cout << ans[i] << endl;
}