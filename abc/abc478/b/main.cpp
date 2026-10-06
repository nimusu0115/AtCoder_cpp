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
    int N,V;
    cin >> N >> V;
    vector<int> W(N);
    rep(i,N) cin >> W[i];

    int ans = 0;
    rep(i,N) rep(j,N) rep(k,N){
        if(i == j || i == k || j == k) continue;
        if(i + j + k + 3 <= V) chmax(ans,W[i] + W[j] + W[k]);
    }
    cout << ans << endl;
}