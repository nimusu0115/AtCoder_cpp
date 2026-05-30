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
ll prm = 998244353;

ll keta(ll x){
    ll k = 0;
    while(x > 0){
        x /= 10;
        k++;
    }
    return k;
}

ll pw(ll a,ll b){
    ll res = 1;
    while(b > 0){
        res *= a;
        b--;
    }
    return res;
}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        ll N,M;
        cin >> N >> M;

        ll ans = 0;
        int k = keta(N);
        onerep(i,k){
            //cout << 4 - T << " " << ans << endl;
            ll A = 1;
            rep(j,i) A = (A * 10) % M;
            if(i == k){
                if(A == 0){
                ll q = (N / M) % prm;
                ll qq = N % prm;
                ll qqq = 1;
                rep(j,i - 1) qqq = (qqq * 10) % prm;
                qqq = (qqq - 1 + prm) % prm;
                qq = (qq - qqq + prm) % prm;
                ans = (ans + q * qq) % prm;
                //cout << 4 - T << " " << 999 << q << " " << qq << endl;
                continue;
                }
                else if(A == 1){
                    ll q = N % prm;
                    ll qq = N % prm;
                    ll qqq = 1;
                    rep(j,i - 1) qqq = (qqq * 10) % prm;
                    qqq = (qqq - 1 + prm) % prm;
                    qq = (qq - qqq + prm) % prm;
                    ans = (ans + q * qq) % prm;
                    continue;
                }
                A--;
                ll c = gcd(A,M);
                ll m = M / c;
                ll q = (N / m) % prm;
                ll qq = N % prm;
                ll qqq = 1;
                rep(j,i - 1) qqq = (qqq * 10) % prm;
                qqq = (qqq - 1 + prm) % prm;
                qq = (qq - qqq + prm) % prm;
                ans = (ans + q * qq) % prm;
                //cout << 4 - T << " " << c << " " << A << " " << M << endl;
            }
            if(A == 0){
                ll q = (N / M) % prm;
                ll qq = 9 % prm;
                rep(j,i - 1) qq = (qq * 10) % prm;
                qq = (qq - 1 + prm) % prm;
                ans = (ans + q * qq) % prm;
                continue;
            }
            else if(A == 1){
                ll q = N % prm;
                ll qq = 9 % prm;
                rep(j,i - 1) qq = (qq * 10) % prm;
                qq = (qq - 1 + prm) % prm;
                ans = (ans + q * qq) % prm;
                continue;
            }
            A--;
            ll c = gcd(A,M);
            ll m = M / c;
            ll q = (N / m) % prm;
            ll qq = 9 % prm;
            rep(j,i - 1) qq = (qq * 10) % prm;
            qq = (qq - 1 + prm) % prm;
            ans = (ans + q * qq) % prm;
        }

        cout << ans << endl;
    }
}