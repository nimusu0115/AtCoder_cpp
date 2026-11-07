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
    int N;
    cin >> N;
    vector<ll> X(N);
    rep(i,N) cin >> X[i];

    rep(i,N){
        if(i == 0){
            cout << (X[N - 1] - X[0]) / 2 << endl;
            continue;
        }
        if(i == N - 1){
            cout << (X[N - 1] - X[0]) / 2 << endl;
            continue;
        }
        ll RR = (X[N - 1] - X[i]) / 2;
        ll RL = (X[i + 1] - X[0]) / 2;
        ll ansr = max(RR,RL);

        ll LL = (X[i] - X[0]) / 2;
        ll LR = (X[N - 1] - X[i - 1]) / 2;
        ll ansl = max(LR,LL);

        cout << min(ansr,ansl) << endl;
    }
}