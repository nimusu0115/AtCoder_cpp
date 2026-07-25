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
    int M,D;
    cin >> M >> D;
    string S;
    cin >> S;

    int ans = 0;
    rep(i,M){
        if(S[i] == 'G') continue;
        bool flg = false;
        onerep(j,D) if(i - j >= 0 && S[i - j] == 'G') flg = true;
        onerep(j,D) if(i + j < M && S[i + j] == 'G') flg = true;
        if(!flg) ans++;
    }

    cout << ans << endl;
}