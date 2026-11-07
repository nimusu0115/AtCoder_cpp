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

int main() {
    vector<string> S(5);
    rep(i,5) cin >> S[i];

    int ans = 100;
    rep(i,5){
        int cnt = 0;
        rep(j,5) if(S[i][j] == '.') cnt++;
        chmin(ans,cnt);
    }
    rep(j,5){
        int cnt = 0;
        rep(i,5) if(S[i][j] == '.') cnt++;
        chmin(ans,cnt);
    }

    int cnt = 0;
    rep(i,5){
        if(S[i][i] == '.') cnt++;
    }
    chmin(ans,cnt);
    int cnt2 = 0;
    rep(i,5){
        if(S[i][4 - i] == '.') cnt2++;
    }
    chmin(ans,cnt2);
    cout << ans << endl;
}