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
// a を現在値と b の大きい方／小さい方に更新する。
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

// 通常のNimで先手必勝なら true を返す。heaps[i]は各山の石の個数。
bool nim(const vector<ll>& heaps) {
    ll nim_sum = 0;
    for (ll count : heaps) {
        nim_sum ^= count;
    }

    return nim_sum != 0;
}

// 各手で1つの山から1～K個を取り除くNimで、先手必勝なら true を返す。
// 前提: K >= 1。
bool Knim(const vector<ll>& heaps,ll K) {
    ll nim_sum = 0;
    for (ll count : heaps) {
        nim_sum ^= count % (K + 1);
    }

    return nim_sum != 0;
}

// 関数を問題ごとに呼び出すためのエントリーポイント。
int main() {
}
