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

// 軸に平行な2つの直方体が共通して占める部分の体積を返す。
// minX={x最小,y最小,z最小}, maxX={x最大,y最大,z最大} とする。
ll getIntersectionVolume(const ll min1[3], const ll max1[3], const ll min2[3], const ll max2[3]) {
    ll dx = max(0LL, min(max1[0], max2[0]) - max(min1[0], min2[0]));
    ll dy = max(0LL, min(max1[1], max2[1]) - max(min1[1], min2[1]));
    ll dz = max(0LL, min(max1[2], max2[2]) - max(min1[2], min2[2]));

    return dx * dy * dz;
}

// 軸に平行な3つの直方体すべてが共通して占める部分の体積を返す。
ll getIntersectionVolume3(const ll min1[3], const ll max1[3], const ll min2[3], const ll max2[3], const ll min3[3], const ll max3[3]) {
    ll dx = max(0LL, min({max1[0], max2[0], max3[0]}) - max({min1[0], min2[0], min3[0]}));
    ll dy = max(0LL, min({max1[1], max2[1], max3[1]}) - max({min1[1], min2[1], min3[1]}));
    ll dz = max(0LL, min({max1[2], max2[2], max3[2]}) - max({min1[2], min2[2], min3[2]}));

    return dx * dy * dz;
}

// 関数を問題ごとに呼び出すためのエントリーポイント。
int main() {
}
