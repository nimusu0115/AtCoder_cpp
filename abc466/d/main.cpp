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
    vector<int> R(M),C(M),yoko(N,0),tate(N,0);
    rep(i,M) cin >> R[i] >> C[i];

    rep(i,M){
        chmax(yoko[R[i] - 1],i + 1);
        chmax(tate[C[i] - 1],i + 1);
    }

    int ans = 0;
    rep(i,M){
        if(yoko[R[i] - 1] == i + 1 && tate[C[i] - 1] == i + 1) ans++;
    }

    cout << ans << endl;
}