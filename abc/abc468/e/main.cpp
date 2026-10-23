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
    vector<ll> A(N);
    rep(i,N) cin >> A[i];
    vector<mint> harm1(N,mint(0)),harm2(N,mint(0));

    onerep(i,N){
        if(i == 1){
            harm1[i - 1] = 1;
            harm2[i - 1] = mint(i) / N;
        }else{
            harm1[i - 1] = harm1[i - 2] +  mint(1) / (N - i + 1);
            harm2[i - 1] = harm2[i - 2] +  mint(i) / (N - i + 1);
        }
    }

    mint ans = 0;

    onerep(i,N){
        ans += mint(A[i - 1]) * min(i,N - i + 1);
        ans += mint(A[i - 1]) * (harm1[max(i,N - i + 1) - 1] - harm1[min(i,N - i + 1) - 1]);
        ans += A[i - 1] * harm2[min(i,N - i + 1) - 1];
    }
    
    cout << ans.val() << endl;
}