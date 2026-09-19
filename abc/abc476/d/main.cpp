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
    ll N,M;
    cin >> N >> M;
    ll K,X,Y;
    cin >> K;
    cin >> X >> Y;
    vector<ll> A(N),B(M),AA(N,0);
    rep(i,N) cin >> A[i];
    rep(i,M) cin >> B[i];
    sort(ALL(A));
    sort(ALL(B));

    vector<bool> Abool(N,false),Bbool(M,false);
    AA = A;
    rep(i,N){
        if(i == 0) continue;
        AA[i] = A[i] + AA[i - 1];
    }

    ll ans = 0,ans2 = 0;

    rep(i,M){
        if(Y * K >= B[i]){
            Y -= (B[i] + K - 1) / K;
            X += ((B[i] + K - 1) / K) * K - B[i];
            Bbool[i] = true;
            ans2++;
        }
    }

    ll money = X + Y * K;
    auto itr = upper_bound(ALL(AA),money);
    ll pp;
    if(money >= AA[N - 1]) pp = N;
    else pp = distance(AA.begin(),itr);
    ans = ans2 + pp;

    //cout << ans2 << " " << pp << endl;
    //cout << money << endl;

    rrep(i,M){
        if(!Bbool[i]) continue;
        money += B[i];
        auto itr = upper_bound(ALL(AA),money);
        ans2--;
        ll p;
        if(money >= AA[N - 1]) p = N;
        else p = distance(AA.begin(),itr);
        chmax(ans,ans2 + p);
        //cout << i << " " << ans2 << " " << p << endl;
    }

    cout << ans << endl;
}