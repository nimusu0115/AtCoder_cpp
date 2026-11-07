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
    ll H,W,N,Q;
    cin >> H >> W >> N >> Q;
    vector<ll> R(N),C(N),tate,yoko;
    rep(i,N) cin >> R[i] >> C[i];
    rep(i,N) tate.push_back(R[i]);
    rep(i,N) yoko.push_back(C[i]);
    sort(ALL(tate));
    sort(ALL(yoko));

    while(Q > 0){
        Q--;

        int c;
        cin >> c;
        if(c == 1){
            int u,d;
            cin >> u >> d;

            auto itrd = lower_bound(ALL(tate),d + 1);
            auto itru = lower_bound(ALL(tate),u);
            cout << distance(itru,itrd) << endl;
        }
        if(c == 2){
            int l,r;
            cin >> l >> r;

            auto itrr = lower_bound(ALL(yoko),r + 1);
            auto itrl = lower_bound(ALL(yoko),l);
            cout << distance(itrl,itrr) << endl;
        }
    }
}