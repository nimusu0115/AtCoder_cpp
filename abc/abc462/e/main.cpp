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
    int T;
    cin >> T;

    while(T > 0){
        T--;

        ll A,B,X,Y;
        cin >> A >> B >> X >> Y;

        if(X < 0) X = -X;
        if(Y < 0) Y = -Y;
        if(A > B) swap(A,B),swap(X,Y);

        ll ans = 0;
        ll m = min(X,Y);
        if(X > Y){
            ans += (2 * m + 1) * A;
            X -= Y + 1;
            if(X == 0){
                cout << ans << endl;
                continue;
            }
            
        }
        
    }
}