#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int main() {
    ll N,K,M,kyodo = 0,ans = 0,r = 0;
    cin >> N >> K >> M;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];

    rep(i,N){
        if(i != 0) kyodo -= A[i - 1];
        if(i == 0) kyodo = A[i];
        while((kyodo < M || r - i + 1 < K) && r < N - 1){
            r++;
            kyodo += A[r];
        }
        if(kyodo >= M && r - i + 1 >= K) ans += N - r;
    }
    cout << ans << endl;
}