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

// Nimの勝敗を出力する関数（trueなら先手必勝）
bool nim(const vector<ll>& heaps) {
    ll nim_sum = 0;
    for (int count : heaps) {
        nim_sum ^= count;
    }

    if(nim_sum == 0) return false;
    else return true;
}

// K個までしか石を移動できないNimの勝敗を出力する関数（trueなら先手必勝）
bool Knim(const vector<ll>& heaps,ll K) {
    ll nim_sum = 0;
    for (ll count : heaps) {
        nim_sum ^= count % (K + 1);
    }

    if(nim_sum == 0) return false;
    else return true;
}

int main() {
}