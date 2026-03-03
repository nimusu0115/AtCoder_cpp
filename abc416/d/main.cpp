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

        ll N,M;
        cin >> N >> M;
        vector<ll> A(N),B(N);
        rep(i,N){
            ll a;
            cin >> a;
            A[i] = a % M;
        }
        rep(i,N){
            ll b;
            cin >> b;
            B[i] = b % M;
        }

        sort(ALL(A));
        reverse(ALL(A));
        sort(ALL(B));
        
        int a = 0,b = 0,match = 0;
        while(a < N && b < N){
            if(A[a] + B[b] >= M){
                a++;
                b++;
                match++;
            }
            else b++;
        }

        ll sum = 0;
        rep(i,N) sum += A[i] + B[i];
        cout << sum - M * match << endl;
    }
}