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
    ll N,K;
    cin >> N >> K;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];
    set<ll> s;
    vector<ll> ss;
    rep(i,N) s.insert(A[i] % K);
    for(auto v : s) ss.push_back(v);
    ll ans = 0;
    rep(i,ss.size() - 1) chmax(ans,ss[i + 1] - ss[i]);
    chmax(ans,ss[0] + K - ss.back());
    cout << K - ans << endl;
}