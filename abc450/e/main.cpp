#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1'000'000'000;
const ll llinf = 2'000'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}
string X,Y;
vector<ll> length;
vector<pair<ll,ll>> fib;
map<char,ll> cX,cY;
ll solve(ll x,char C){
    if(x == 0) return 0;
    ll res = 0;
    rrep(i,length.size()){
        if(length[i] <= x){
            res += cX[C] * fib[i].first + cY[C] * fib[i].second;
            x -= length[i];
        }
    }
    rep(i,x) if(X[i] == C) res++;
    return res;
}

int main() {
    cin >> X >> Y;
    int Q;
    cin >> Q;

    for(auto c : X) cX[c]++;
    for(auto c : Y) cY[c]++;

    ll a = X.size(),b = Y.size();
    length.push_back(a);
    length.push_back(b);
    fib.push_back({1,0});
    fib.push_back({0,1});
    int m = 2;
    while(length.back() <= llinf){
        length.push_back(length[m - 1] + length[m - 2]);
        ll fir = fib[m - 1].first + fib[m - 2].first;
        ll sec = fib[m - 1].second + fib[m - 2].second;
        fib.push_back({fir,sec});
    }

    while(Q > 0){
        ll L,R;
        char C;
        cin >> L >> R >> C;

        cout << solve(R,C) - solve(L,C) << endl;
    }
}