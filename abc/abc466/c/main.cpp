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
    int N;
    cin >> N;

    ll l = 1,r = 2;
    ll ans = 0;

    while(r <= N){

        cout << "?" << " "<< l << " " << r << endl;
        cout.flush();
        string S;
        cin >> S;

        if(S == "Yes"){
            r++;
        }
        if(S == "No"){
            ans += r - l - 1;
            l++;
            if(l == r) r++;
        }
    }
    cout << ans << endl;
    cout.flush();
}