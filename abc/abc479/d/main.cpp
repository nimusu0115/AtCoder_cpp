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
    int N,Q;
    cin >> N >> Q;
    vector<ll> L(N),R(N);
    rep(i,N - 1) cin >> L[i + 1];
    L[0] = llinf;
    rep(i,N - 1) cin >> R[i];
    R[N - 1] = llinf;

    vector<ll> Lmin(N),Rmin(N);
    rrep(i,N){
        if(i == N - 1){
            Lmin[i] = L[i];
            continue;
        }
        Lmin[i] = min(Lmin[i + 1],L[i]);
    }
    rep(i,N){
        if(i == 0){
            Rmin[i] = R[i];
            continue;
        }
        Rmin[i] = min(Rmin[i - 1],R[i]);
    }

    while(Q > 0){
        Q--;

        int s,t;
        cin >> s >> t;
        s--,t--;

        if(s < t){
            cout << min(R[s],L[s] + Rmin[s]) << endl;;
        }
        if(s > t){
            cout << min(L[s],R[s] + Lmin[s]) << endl;
        }
    }

    /*rep(i,N) cout << Lmin[i];
    cout << endl;
    rep(i,N) cout << Rmin[i];
    cout << endl;*/
}