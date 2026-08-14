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
    int N;
    cin >> N;
    vector<int> P(N),Q(N),A(N);
    rep(i,N) cin >> P[i];
    rep(i,N) cin >> Q[i];
    rep(i,N) A[i] = i + 1;

    int ans = 0;
    do{
        if(P < A && A < Q) ans++;
    } while(next_permutation(ALL(A)));

    cout << ans << endl;
}