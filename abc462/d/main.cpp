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
    ll N,D;
    cin >> N >> D;

    vector<ll> S(N),T(N);
    rep(i,N) cin >> S[i] >> T[i];

    vector<ll> imos(1'000'010);

    rep(i,N){
        imos[S[i]]++;
        imos[T[i]]--;
    }

    rep(i,1'000'010) if(i != 0) imos[i] += imos[i - 1];

    set<ll> s;
    map<ll,ll> m;
    rep(i,D){
        s.insert(imos[i]);
        m[imos[i]]++;
    }

    ll ans = 0;
    ans += *s.begin() * (*s.begin() - 1) / 2;

    for(ll i = D;i < 1'000'010;i++){
        s.insert(imos[i]);
        m[imos[i]]++;
        m[imos[i - D]]--;
        if(m[imos[i - D]] == 0) s.erase(imos[i - D]);
        ans += *s.begin() * (*s.begin() - 1) / 2;
    }

    cout << ans << endl;
}