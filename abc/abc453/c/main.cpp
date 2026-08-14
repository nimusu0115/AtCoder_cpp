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

int main() {
    int N;
    cin >> N;
    vector<ll> L(N);
    rep(i,N) cin >> L[i];

    int ans = 0;
    rep(bit,pw(2,N)){
        ll pos = 0;

        int res = 0;
        rep(i,N){
            if(((bit>>i) & 1) == 1){
                if(pos < 0 && 0 <= pos + L[i]) res++;
                pos += L[i];
            }
            else{
                if(pos >= 0 && 0 > pos - L[i]) res++;
                pos -= L[i];
            }
        }

        chmax(ans,res);
    }

    cout << ans << endl;
}