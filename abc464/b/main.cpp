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
    int H,W;
    cin >> H >> W;
    vector<string> C(H);
    rep(i,H) cin >> C[i];
    int u = 0,d = H - 1,l = 0,r = W - 1;

    rep(i,H){
        bool flg = true;
        rep(j,W) if(C[i][j] == '#') flg = false;
        if(flg) u++;
        else break;
    }

    rrep(i,H){
        bool flg = true;
        rep(j,W) if(C[i][j] == '#') flg = false;
        if(flg) d--;
        else break;
    }

    rep(j,W){
        bool flg = true;
        rep(i,H) if(C[i][j] == '#') flg = false;
        if(flg) l++;
        else break;
    }

    rrep(j,W){
        bool flg = true;
        rep(i,H) if(C[i][j] == '#') flg = false;
        if(flg) r--;
        else break;
    }

    for(int i = u;i <= d;i++){
        for(int j = l;j <= r;j++){
            cout << C[i][j];
        }
        cout << endl;
    }
}