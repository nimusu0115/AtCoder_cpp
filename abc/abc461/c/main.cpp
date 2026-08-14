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
    int N,K,M;
    cin >> N >> K >> M;
    vector<int> C(N);
    vector<ll> V(N);
    rep(i,N) cin >> C[i] >> V[i];

    vector<ll> clr(N);
    rep(i,N) chmax(clr[C[i] - 1],V[i]);
    sort(ALL(clr));
    reverse(ALL(clr));

    multiset<ll> m;
    rep(i,N) m.insert(V[i]);

    ll ans = 0;
    rep(i,M){
        ans += clr[i];
        m.erase(m.find(clr[i]));
    }

    rep(i,K - M){
        ans += *--m.end();
        m.erase(m.find(*--m.end()));
    }

    cout << ans << endl;
}