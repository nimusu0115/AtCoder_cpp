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
    ll G,M,D,K,V;
    cin >> G >> M >> D >> K >> V;
    if(K * V >= M - G){
        if((M - G) * D >= G * V) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    else{
        if(K * D * V + M - G - K * V - G * V >= 0) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}