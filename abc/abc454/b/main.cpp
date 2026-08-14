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
    int N,M;
    cin >> N >> M;
    vector<int> F(N);
    rep(i,N) cin >> F[i];

    vector<int> c(M,0);
    rep(i,N) c[F[i] - 1]++;

    bool flg = true;
    rep(i,M) if(c[i] >= 2) flg = false;
    if(flg) cout << "Yes" << endl;
    else cout << "No" << endl;

    bool flg2 = true;
    rep(i,M) if(c[i] == 0) flg2 = false;
    if(flg2) cout << "Yes" << endl;
    else cout << "No" << endl;
}