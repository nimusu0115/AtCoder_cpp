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
    int N,D;
    cin >> N >> D;
    vector<ll> X(N);
    rep(i,N) cin >> X[i];

    vector<int> ans;
    rep(i,N){
        bool flg = true;
        rep(j,N){
            if(i == j) continue;
            if(abs(X[i] - X[j]) < D) flg = false;
        }
        if(flg) ans.push_back(i + 1);
    }

    cout << ans.size() << endl;
    rep(i,ans.size()){
        cout << ans[i];
        if(i != ans.size() - 1) cout << " ";
    }
    cout << endl;
}