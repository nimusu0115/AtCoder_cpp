#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int main() {
    ll N,V;
    cin >> N >> V;
    vector<ll> D(N - 1),T(N);
    rep(i,N - 1) cin >> D[i];
    rep(i,N - 1) cin >> T[i + 1];

    ll D_sum = 0;
    bool flg = false;
    rep(i,N - 1){
        D_sum += D[i];
        if(D_sum / V < T[i + 1]){
            if(flg) cout << " ";
            cout << i + 2;
            flg = true;
        }
    }

    if(flg) cout << endl;
    else cout << -1 << endl;
}