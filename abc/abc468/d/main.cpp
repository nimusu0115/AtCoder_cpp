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
    string s;
    cin >> s;
    int n = s.size();
    
    //'#'の追加
    string S(2 * n + 1, '#');
    for (int i = 0; i < n; i++) S[2 * i + 1] = s[i];
    n = 2 * n + 1;

    vector<ll> rad1(n),rad2(n);
    int c = 0, r = 0;

    while (c < n) {
        // cを中心に同じ文字がどこまで連続するか
        while (0 <= c - r && c + r < n && S[c - r] == S[c + r]) r++;
        rad1[c] = r;

        //回文の長さに応じて利用可能な範囲を確認しつつメモ
        int k = 1;
        while (0 <= c - k && k + rad1[c - k] < r) {
        rad1[c + k] = rad1[c - k];
        k++;
        }
        //すでに計算が終わった分だけ中心と探索半径をずらす
        c += k;
        r -= k;
    }

    rep(i,n){
        int j = rad1[i];
        while(0 <= i - j && i + j < n){
            if(j == rad1[i]){
                j++;
                continue;
            }
            if(S[i - j] == S[i + j]) j++;
            else break;
        }
        rad2[i] = j;
    }

    //'＃'分の補正
    for (int i = 0; i < n; i++) {
        if (i % 2 == 0)
        rad2[i] = (rad2[i] - 1) / 2;
        else
        rad2[i] /= 2;
    }

    ll ans = 0;
    rep(i,n) ans += rad2[i];
    cout << ans << endl;
    //rep(i,n) cout << rad2[i] << endl;
}