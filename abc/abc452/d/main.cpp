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
    string S,T;
    cin >> S >> T;

    int N = S.size(),M = T.size();

    vector<vector<int>> V(26,vector<int>(N + 1,inf));
    rep(i,26){
        rrep(j,N + 1){
            if(j == 0){
                V[i][j] = 0;
                continue;
            }
            if(S[j - 1] - 'a' == i) V[i][j] = j;
            else if(j != N) V[i][j] = V[i][j + 1];
        }
    }

    ll ans = 0;
    onerep(i,N){
        int pos = i;
        rep(j,M){
            if(pos > N){
                pos = inf;
                continue;
            }
            int next = T[j] - 'a';
            pos = V[next][pos] + 1;
        }
        if(pos >= inf) ans += N - i + 1;
        else ans += pos - 1 - i;
    }
    cout << ans << endl;
}