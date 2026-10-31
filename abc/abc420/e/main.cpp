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
    int N,Q;
    cin >> N >> Q;

    vector<bool> isblack(N,false);
    vector<int> blacksize(N,0);
    dsu uf(N);

    while(Q > 0){
        Q--;

        int c;
        cin >> c;

        if(c == 1){
            int u,v;
            cin >> u >> v;
            u--,v--;

            if(uf.same(u,v)) continue;
            int ublack = blacksize[uf.leader(u)];
            int vblack = blacksize[uf.leader(v)];
            uf.merge(u,v);
            blacksize[uf.leader(u)] = ublack + vblack;
        }
        if(c == 2){
            int v;
            cin >> v;
            v--;

            if(isblack[v]) blacksize[uf.leader(v)]--,isblack[v] = false;
            else blacksize[uf.leader(v)]++,isblack[v] = true;

        }
        if(c == 3){
            int v;
            cin >> v;
            v--;

            if(blacksize[uf.leader(v)] > 0) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
    }
}