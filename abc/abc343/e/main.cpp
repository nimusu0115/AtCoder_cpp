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

ll getIntersectionVolume(ll min1[3], ll max1[3], ll min2[3], ll max2[3]) {
    ll dx = max(0LL, min(max1[0], max2[0]) - max(min1[0], min2[0]));
    ll dy = max(0LL, min(max1[1], max2[1]) - max(min1[1], min2[1]));
    ll dz = max(0LL, min(max1[2], max2[2]) - max(min1[2], min2[2]));

    return dx * dy * dz;
}

ll getIntersectionVolume3(ll min1[3], ll max1[3], ll min2[3], ll max2[3], ll min3[3], ll max3[3]) {
    ll dx = max(0LL, min({max1[0], max2[0], max3[0]}) - max({min1[0], min2[0], min3[0]}));
    ll dy = max(0LL, min({max1[1], max2[1], max3[1]}) - max({min1[1], min2[1], min3[1]}));
    ll dz = max(0LL, min({max1[2], max2[2], max3[2]}) - max({min1[2], min2[2], min3[2]}));

    return dx * dy * dz;
}

int main() {
    int V1,V2,V3;
    cin >> V1 >> V2 >> V3;

    rep(i,15) rep(j,15) rep(k,15) rep(l,15) rep(m,15) rep(n,15){
        ll min0[3] = {0,0,0};
        ll max0[3] = {7,7,7};
        ll min1[3] = {i - 7,j - 7,k - 7};
        ll max1[3] = {i,j,k};
        ll min2[3] = {l - 7,m - 7,n - 7};
        ll max2[3] = {l,m,n};

        int v1,v2,v3;
        v3 = getIntersectionVolume3(min0, max0, min1, max1, min2, max2);
        v2 = getIntersectionVolume(min0, max0, min1, max1) + getIntersectionVolume(min0, max0, min2, max2) + getIntersectionVolume(min1, max1, min2, max2) - 3 * v3;
        v1 = 3 * 7 * 7 * 7 - v2 * 2 - v3 * 3;
        if(v1 == V1 && v2 == V2 && v3 == V3) {
            cout << "Yes" << endl;
            cout << 0 << " " << 0 << " " << 0 << " ";
            cout << i - 7 << " " << j - 7 << " " << k - 7 << " ";
            cout << l - 7 << " " << m - 7 << " " << n - 7 << endl;
            return 0;
        }
    }

    cout << "No" << endl;
}