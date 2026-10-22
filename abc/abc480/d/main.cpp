//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i,n) for(ll i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}
ll N;
vector<ll> A,AA,Nsum,AAA;

ll solve(ll x){
    if(x == N * (N + 1) / 2){
        return AAA[N - 1];
    }
    if(x == 0){
        return 0LL;
    }
    ll res = 0;
    auto itr = upper_bound(ALL(Nsum),x);
    itr--;
    ll y = distance(Nsum.begin(),itr);
    res += AAA[y];

    ll z = x - Nsum[y];
    if(z > 0) res += AA[z - 1];

    return res;
}

int main() {
    ll Q;
    cin >> N >> Q;
    A.resize(N);
    AA.resize(N);
    AAA.resize(N);
    Nsum.resize(N,0);
    rep(i,N) cin >> A[i];
    AA = A;
    rep(i,N){
        if(i == 0) continue;
        AA[i] += AA[i - 1];
    }
    AAA = AA;
    rep(i,N){
        if(i == 0) continue;
        AAA[i] += AAA[i - 1];
    }
    rep(i,N) Nsum[i] = (i + 1) * (i + 2) / 2;

    while(Q > 0){
        Q--;

        ll L,R;
        cin >> L >> R;

        cout << solve(R) - solve(L - 1) << endl;
    }
}