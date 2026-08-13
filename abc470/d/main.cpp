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
    int N,Q;
    cin >> N >> Q;
    vector<int> P(N);
    rep(i,N) cin >> P[i];
    vector<int> ans(N);
    rep(i,N){
        ans[P[i] - 1] = i + 1;
    }
    while(Q > 0){
        Q--;

        int c;
        cin >> c;
        if(c == 1){
            int x,y;
            cin >> x >> y;
            swap(P[x - 1],P[y - 1]);
            swap(ans[P[x - 1] - 1],ans[P[y - 1] - 1]);
        }
        if(c == 2){
            swap(P,ans);
        }
        /*rep(i,N) cout << P[i];
        cout << " ";
        rep(i,N) cout << ans[i];
        cout << endl;*/
    }
    rep(i,N){
        cout << P[i];
        if(i != N - 1) cout << " ";
    }
    cout << endl;
}