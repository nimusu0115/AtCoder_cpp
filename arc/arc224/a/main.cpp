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

ll keta(ll x,int a){
    ll k = 0;
    while(x > 0){
        x /= a;
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

bool solve(ll x){
    int k = keta(x,10);

    int a = 0;
    int b = 0;
    rep(i,k){
        if((x / pw(10,i)) % 10 == 0) a++;
        else a = 0;
        chmax(b,a);
    }
    if(b >= 2) return true;
    else return false;
}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        ll K;
        cin >> K;

        ll p = K;
        ll ans = 0;
        while(true){
            if(solve(p)){
                cout << p << endl;
                break;
            }
            else p += K;
        }
    }
}