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
    int N,M;
    cin >> N >> M;
    vector<bool> drink(M,true);
    rep(i,N){
        int L;
        cin >> L;
        vector<int> X(L);
        rep(i,L) cin >> X[i];
        bool flg = false;
        rep(i,L){
            if(flg) continue;
            if(drink[X[i] - 1]){
                cout << X[i] << endl;
                flg = true;
                drink[X[i] - 1] = false;
            }
        }
        if(!flg) cout << 0 << endl;
    }
}