#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int gokan_distance(vector<int> P,vector<int> Q){
    int cnt = 0;
    int n = P.size();
    vector<bool> seen(n,false),P_inverse(n);
    rep(i,n) P_inverse[P[i]] = i;
    rep(i,n){
        if(seen[i]) continue;
        cnt++;
        seen[i] = true;
        int next = P_inverse[Q[i]];                                   
        while(next != i){
            seen[next] = true;
            next = P_inverse[Q[next]];
        }
    }
    return n - cnt;
}

int main() {
    int N,K;
    cin >> N >> K;
    vector<vector<int>> C(N,vector<int>(N));
    rep(i,N) rep(j,N) cin >> C[i][j];

    vector<int> P(N),ini(N);
    rep(i,N) P[i] = i;
    rep(i,N) ini[i] = i;

    ll ans = 0;
    do{
        if(gokan_distance(P,ini) <= K){
            ll kouka = C[P[N - 1]][P[0]];
            rep(i,N - 1) kouka += C[P[i]][P[i + 1]];
            ans = max(ans,kouka);
        }

    } while (next_permutation(ALL(P)));

    cout << ans << endl;
}