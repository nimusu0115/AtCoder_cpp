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
    int N;
    cin >> N;
    vector<int> X(N),Y(N);
    rep(i,N) cin >> X[i] >> Y[i];

    vector<pair<int,int>> p(N);
    rep(i,N) p[i] = {X[i],Y[i]};
    sort(ALL(p));

    int ans = 0;
    int m;
    rep(i,N){
        if(i == 0){
            ans++;
            m = p[i].second;
            continue;
        }
        if(p[i].second < m){
            ans++;
            m = p[i].second;
        }
    }

    cout << ans << endl;
}