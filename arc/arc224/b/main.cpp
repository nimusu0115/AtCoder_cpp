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

ll pw(ll a,ll b){
    ll res = 1;
    while(b > 0){
        res *= a;
        b--;
    }
    return res;
}

ll sq(ll x){
    ll ok = 0,ng = pw(10,9) + 10;
    while(ng - ok > 1){
        ll m = (ng + ok) / 2;
        if(m * m <= x) ok = m;
        else ng = m;
    }
    return ok;
}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        ll N;
        cin >> N;

        ll n = sq(N);
        N -= n * n;

        ll ans = 0;
        ans += 2 * n * (n - 1);

        if(N == 0){
            cout << ans << endl;
        }
        else{
            if(N > n){
                ans += 2 * n - 1;
                N -= n;
            }
            ans += 2 * N - 1;

            cout << ans << endl;
        }
    }
}