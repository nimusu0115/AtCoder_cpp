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

//拡張ユークリッドの互除法
// ax + by = gcd(a, b) を満たす (x, y) を求め、gcd(a, b) を返す
long long extGCD(long long a, long long b, long long &x, long long &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    
    long long x1, y1;
    long long g = extGCD(b, a % b, x1, y1);

    x = y1;
    y = x1 - (a / b) * y1;
    
    return g;
}

//一次不定方程式 ax + by = c の解を求める関数
//解が存在する場合は true と特殊解 (x, y) を返し、存在しない場合は false を返す
bool solveDiophantine(long long a, long long b, long long c, long long &x, long long &y, long long &g) {
    g = extGCD(abs(a), abs(b), x, y);

    if (c % g != 0) {
        return false;
    }

    long long scale = c / g;
    x *= scale;
    y *= scale;

    if (a < 0) x = -x;
    if (b < 0) y = -y;

    return true;
}

int main() {
}