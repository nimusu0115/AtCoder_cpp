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
    int N;
    cin >> N;
    vector<ll> D(N);
    rep(i,N) cin >> D[i];

    ll time = 0,pre = 0;
    rep(i,N){
        if(i == 0) time += D[i];
        else if(D[i - 1] < D[i]) time += D[i] / 2;
        else time += D[i];
    }

    cout << time << endl;
}