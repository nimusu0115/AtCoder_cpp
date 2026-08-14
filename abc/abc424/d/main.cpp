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
int ans;
void rec(vector<string> S,int n,int cnt){
    //if(cnt > 9) return;
    if(n == (H - 1) * (W - 1)){
        chmin(ans,cnt);
        return;
    }

    int h = n / (W - 1);
    int w = n % (W - 1);

    int c = 0;
    rep(dir,4){
        int nh = h + dx[dir];
        int nw = w + dy[dir];
        if(S[nh][nw] == '.') c++;
    }
    if(c != 0) rec(S,n + 1,cnt);
    else{
        for(int dir = 2;dir < 4;dir++){
            auto T = S;
            int nh = h + dx[dir];
            int nw = w + dy[dir];
            T[nh][nw] = '.';
            rec(T,n + 1,cnt + 1);
        }
    }
}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        cin >> H >> W;
        vector<string> S(H);
        rep(i,H) cin >> S[i];
        ans = inf;

        rec(S,0,0);

        cout << ans << endl;
    }
}