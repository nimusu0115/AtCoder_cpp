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

int main() {
    int H,W,K;
    cin >> H >> W >> K;
    char c1,c2;
    cin >> c1 >> c2;
    vector<string> S(H);
    rep(i,H) cin >> S[i];

    rep(i,H * K){
        rep(j,W * K){
            if(S[i / K][j / K] == '#') cout << c1;
            else cout << c2;
        }
        cout << endl;
    }
}