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

        int N,A,B;
        cin >> N >> A >> B;

        if(N % 2 == 1){
            cout << "No" << endl;
            continue;
        }
        if((A + B) % 2 == 0){
            cout << "No" << endl;
            continue;
        }
        cout << "Yes" << endl;
        if(A == 1){
            rep(i,B / 2 - 1){
                rep(j,N - 1) cout << 'D';
                cout << 'R';
                rep(j,N - 1) cout << 'U';
                cout << 'R';
            }
            rep(i,N - 1) cout << 'D';
            cout << 'R';
            rep(i,N - 2) cout << 'U';
            rep(i,(N - B) / 2) cout << "RURD";
            rep(i,(N - 2) / 2){
                cout << 'D';
                rep(j,N - B - 1) cout << 'L';
                cout << 'D';
                rep(j,N - B - 1) cout << 'R';
            }
            cout << endl;
        }
        else if(B == 1){
            rep(i,A / 2 - 1){
                rep(j,N - 1) cout << 'R';
                cout << 'D';
                rep(j,N - 1) cout << 'L';
                cout << 'D';
            }
            rep(i,N - 1) cout << 'R';
            cout << 'D';
            rep(i,N - 2) cout << 'L';
            rep(i,(N - A) / 2) cout << "DLDR";
            rep(i,(N - 2) / 2){
                cout << 'R';
                rep(j,N - A - 1) cout << 'U';
                cout << 'R';
                rep(j,N - A - 1) cout << 'D';
            }
            cout << endl;
        }
        else if(A % 2 == 0){
            rep(i,(B - 1) / 2 - 1){
                rep(j,N - 1) cout << 'D';
                cout << 'R';
                rep(j,N - 1) cout << 'U';
                cout << 'R';
            }
            rep(i,N - 1) cout << 'D';
            cout << 'R';
            rep(i,(N - A) / 2) cout << "RULU";
            rep(i,A - 1) cout << 'U';
            cout << 'R';
            rep(i,(A - 2) / 2){
                rep(j,N - B) cout << 'R';
                cout << 'D';
                rep(j,N - B) cout << 'L';
                cout << 'D';
            }
            rep(j,N - B) cout << 'R';
            cout << 'D';
            rep(i,N - B - 1) cout << 'L';
            cout << 'D';
            rep(i,(N - B - 1) / 2){
                rep(j,N - A - 1) cout << 'D';
                cout << 'R';
                rep(j,N - A - 1) cout << 'U';
                cout << 'R';
            }
            rep(i,N - A - 1) cout << 'D';
        }
        else if(B % 2 == 0){
            rep(i,(A - 1) / 2 - 1){
                rep(j,N - 1) cout << 'R';
                cout << 'D';
                rep(j,N - 1) cout << 'L';
                cout << 'D';
            }
            rep(i,N - 1) cout << 'R';
            cout << 'D';
            rep(i,(N - B) / 2) cout << "DLUL";
            rep(i,B - 1) cout << 'L';
            cout << 'D';
            rep(i,(B - 2) / 2){
                rep(j,N - A) cout << 'D';
                cout << 'R';
                rep(j,N - A) cout << 'U';
                cout << 'R';
            }
            rep(j,N - A) cout << 'D';
            cout << 'R';
            rep(i,N - A - 1) cout << 'U';
            cout << 'R';
            rep(i,(N - A - 1) / 2){
                rep(j,N - B - 1) cout << 'R';
                cout << 'D';
                rep(j,N - B - 1) cout << 'L';
                cout << 'D';
            }
            rep(i,N - B - 1) cout << 'R';
            cout << endl;
        }
    }
}