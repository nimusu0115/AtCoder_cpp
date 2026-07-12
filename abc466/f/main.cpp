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

        ll N,X;
        cin >> N >> X;
        vector<ll> a(N),A;
        rep(i,N) cin >> a[i];

        int t = 0;
        A.push_back(a[0]);
        rep(i,N){
            if(i == 0) continue;
            if(a[i] < A[t]){
                A.push_back(a[i]);
                t++;
            }
        }

        N = A.size();
        reverse(ALL(A));

        vector<ll> B(N,0);
        rrep(i,N){
            B[i] += X / A[i];
            X %= A[i];
        }

        rrep(i,N){
            if(i == 0) continue;

            ll x = A[i];

            int t = i;
            while(x >= A[0]){
                ll k = distance(A.begin(),lower_bound(ALL(A),x));
                B[k] += (x / A[k]) * B[t];
                x %= A[k];
                t = k;
            }
        }

        cout << B[N - 1] << endl;

        //rep(i,N) cout << B[i] << endl;
        //cout << endl;
    }
}