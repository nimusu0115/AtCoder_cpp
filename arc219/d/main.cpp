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

bool Knim(const vector<ll>& heaps,ll K) {
    ll nim_sum = 0;
    for (int count : heaps) {
        nim_sum ^= count % (K + 1);
    }

    if(nim_sum == 0) return false;
    else return true;
}

int main() {
    int T;
    cin >> T;

    while(T > 0){
        T--;

        ll N,K;
        cin >> N >> K;
        vector<vector<ll>> A(N,vector<ll>(N));

        rep(i,N){
            rep(j,N){
                cin >> A[i][j];
            }
        }

        vector<ll> nim;

        rep(i,N){
            rep(j,N){
                if((i + j) % 2 == 1) nim.push_back(A[i][j]);
            }           
        }

        if(Knim(nim,K)) cout << "Alice" << endl;
        else cout << "Bob" << endl;
    }
}