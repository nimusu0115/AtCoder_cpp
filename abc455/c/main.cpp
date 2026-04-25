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
    int N,K;
    cin >> N >> K;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];

    map<ll,int> m;
    rep(i,N) m[A[i]]++;

    vector<ll> V;
    for(auto v : m) V.push_back(v.first * v.second);

    sort(ALL(V));
    reverse(ALL(V));

    ll ans = 0;
    rep(i,N) ans += A[i];

    rep(i,min(int(V.size()),K)) ans -= V[i];

    cout << ans << endl;
}