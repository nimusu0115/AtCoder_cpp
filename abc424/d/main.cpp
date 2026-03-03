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
const int dx[4] = {0, 0, 1, 1};
const int dy[4] = {0, 1, 0, 1};
int H,W;
int rec(vector<string> S,int cnt){
    if(cnt >= 9) return cnt;
    int h = 0,w = 0;
    rep(i,H - 1){
        rep(j,W - 1){
            if(S[i][j] == '#' && S[i + 1][j] == '#' && S[i][j + 1] == '#' && S[i + 1][j + 1] == '#'){
                rep(dir,4){
                    S[i + dx[dir]][j + dy[dir]] = '.';
                    rec(S,cnt + 1);
                }
            }
        }
    }
}

int solve(vector<string> S){

}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        cin >> H >> W;
        vector<string> S(H);
        rep(i,H) cin >> S[i];
    }
}