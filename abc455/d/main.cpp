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
    int N,Q;
    cin >> N >> Q;
    vector<int> C(Q),P(Q);
    rep(i,Q) cin >> C[i] >> P[i];

    vector<int> card(N + 1,inf),mount(N + 1),cardinv(N + 1);
    onerep(i,N) mount[i] = i;
    onerep(i,N) cardinv[i] = - i;

    rep(i,Q){
        if(cardinv[C[i]] < 0) mount[-cardinv[C[i]]] = inf;
        else card[cardinv[C[i]]] = inf;
        card[P[i]] = C[i];
        cardinv[C[i]] = P[i];
    }

    onerep(i,N){
        if(mount[i] == inf){
            cout << 0;
            if(i != N) cout << " ";
            continue;
        }
        int res = 0;
        int m = mount[i];
        while(m != inf){
            res++;
            m = card[m];
        }
        cout << res;
        if(i != N) cout << " ";
    }
    cout << endl;
}