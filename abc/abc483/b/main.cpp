//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
#define ll long long
#define rep(i,n) for(ll i = 0;i < n;i++)
#define rrep(i,n) for(ll i = n - 1;i >= 0;i--)
#define onerep(i,n) for(ll i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int main() {
    int N,Q;
    cin >> N >> Q;
    vector<int> K(Q),A(N);
    rep(i,N) A[i] = i;
    vector<bool> omote(N,true);
    rep(i,Q) cin >> K[i];

    rep(i,Q){
        reverse(A.begin(),A.begin() + K[i]);
        rep(j,K[i]) omote[A[j]] = omote[A[j]] ^ 1;
    }

    rep(i,N){
        if(omote[A[i]]) cout << A[i] + 1 << endl;
        else cout << -(A[i] + 1) << endl;
    }
}