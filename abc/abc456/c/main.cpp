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
    string S;
    cin >> S;

    ll ans = 0;
    ll lng = 0;
    char pre;
    rep(i,S.size()){
        if(i == 0){
            pre = S[i];
            lng = 1;
            continue;
        }
        else{
            if(S[i] == pre){
                ans += lng * (lng + 1) / 2;
                lng = 1;
            }
            else lng++;
            pre = S[i];
        }
    }
    ans += lng * (lng + 1) / 2;

    cout << ans % 998244353 << endl;
}