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

    if(H == 1 && W == 1){
        cout << 0 << endl;
        return 0;
    }

    if(H == 1){
        rep(i,W){
            if(i == 0 || i == W - 1) cout << 1;
            else cout << 2;
            if(i != W - 1) cout << " ";
        }
        cout << endl;
        return 0;
    }

    if(W == 1){
        rep(i,H){
            if(i == 0 || i == H - 1) cout << 1;
            else cout << 2;
            cout << endl;
        }
        return 0;
    }    

    rep(i,H){
        rep(j,W){
            if((i == 0 && j == 0) || (i == 0 && j == W - 1) || (i == H - 1 && j == 0) || (i == H - 1 && j == W - 1)) cout << 2;
            else if((i == 0) || (j == 0) || (i == H - 1) || (j == W - 1)) cout << 3;
            else cout << 4;
            if(j != W - 1) cout << " ";
        }
        cout << endl;
    }
}