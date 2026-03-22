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
    int N,M;
    cin >> N >> M;
    vector<int> C(M),A(N),B(N);
    rep(i,M) cin >> C[i];
    rep(i,N) cin >> A[i] >> B[i];

    ll ans = 0;
    rep(i,N){
        if(C[A[i] - 1] >= B[i]){
            ans += B[i];
            C[A[i] - 1] -= B[i];
        }
        else{
            ans += C[A[i] - 1];
            C[A[i] - 1] = 0;
        }
    }

    cout << ans << endl;
}