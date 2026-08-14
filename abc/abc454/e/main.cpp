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
        onerep(i,N / 2){
            if(i < (B + 1) / 2){
                rep(j,N - 1) cout << 'D';
                cout << 'R';
                rep(j,N - 1) cout << 'U';
                cout << 'R';
            }
            else if(i == (B + 1) / 2){
                onerep(j,N / 2){
                    if(j < (A + 1) / 2) cout << "RDLD";
                    else if(j == (A + 1) / 2){
                        if(A % 2 == 0) cout << "RD";
                        if(A % 2 == 1) cout << "DR";
                    }
                    else if(j > (A + 1) / 2) cout << "DLDR";
                }
            }
            else if(i > (B + 1) / 2){
                cout << 'R';
                rep(j,N - 1) cout << 'U';
                cout << 'R';
                rep(j,N - 1) cout << 'D';
            }
        }
        cout << endl;
    }
}