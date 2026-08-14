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
    int T;
    cin >> T;
    while(T > 0){
        T--;

        ll Px,Py,Qx,Qy,Rx,Ry,Sx,Sy;
        cin >> Px >> Py >> Qx >> Qy >> Rx >> Ry >> Sx >> Sy;


        if((Qx - Px) * (Sy - Ry) == (Qy - Py) * (Sx - Rx)){
            ll Ax = Qx + Px,Ay = Qy + Py,Bx = Rx + Sx,By = Ry + Sy;
            if((Qy - Py) * (By - Ay) == -(Qx - Px) * (Bx - Ax)) cout << "Yes" << endl;
            else cout << "No" << endl;
        }
        else cout << "Yes" << endl;
    }
}