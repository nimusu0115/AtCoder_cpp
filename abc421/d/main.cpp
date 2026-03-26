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
    ll Rt,Ct,Ra,Ca;
    cin >> Rt >> Ct >> Ra >> Ca;
    ll N,M,L;
    cin >> N >> M >> L;
    queue<pair<char,ll>> A,B;
    rep(i,M){
        char s;
        ll a;
        cin >> s >> a;
        A.push({s,a});
    }
    rep(i,L){
        char t;
        ll b;
        cin >> t >> b;
        B.push({t,b});
    }

    if((Rt + Ct) % 2 != (Ra + Ca) % 2){
        cout << 0 << endl;
        return 0;
    }
    ll ans = 0;
    while(!A.empty() || !B.empty()){
        ll x = min(A.front().second,B.front().second);
        if(Rt == Ra && Ct == Ca){
            if(A.front().first == B.front().first){
                ans += x;
            }
        }
        else{
            if(Rt == Ra){
                if(Ct < Ca && A.front().first == 'R' && B.front().first == 'L'){
                    if(Ca - Ct <= x * 2) ans++;
                }
                if(Ca < Ct && A.front().first == 'L' && B.front().first == 'R'){
                    if(Ct - Ca <= x * 2) ans++;
                }
            }
            if(Ct == Ca){
                if(Rt < Ra && A.front().first == 'D' && B.front().first == 'U'){
                    if(Ra - Rt <= x * 2) ans++;
                }
                if(Ra < Rt && A.front().first == 'U' && B.front().first == 'D'){
                    if(Rt - Ra <= x * 2) ans++;
                }
            }
            if(Ct - Ca == Rt - Ra){
                if(Ra < Rt){
                    if(A.front().first == 'U' && B.front().first == 'R'){
                        if(Rt - Ra <= x) ans++;
                    }
                    if(A.front().first == 'L' && B.front().first == 'D'){
                        if(Rt - Ra <= x) ans++;
                    }
                }
                if(Rt < Ra){
                    if(A.front().first == 'D' && B.front().first == 'L'){
                        if(Ra - Rt <= x) ans++;
                    }
                    if(A.front().first == 'R' && B.front().first == 'U'){
                        if(Ra - Rt <= x) ans++;
                    }
                }
            }
            if(Ca - Ct == Rt - Ra){
                if(Ra < Rt){
                    if(A.front().first == 'U' && B.front().first == 'L'){
                        if(Rt - Ra <= x) ans++;
                    }
                    if(A.front().first == 'R' && B.front().first == 'D'){
                        if(Rt - Ra <= x) ans++;
                    }
                }
                if(Rt < Ra){
                    if(A.front().first == 'L' && B.front().first == 'U'){
                        if(Ra - Rt <= x) ans++;
                    }
                    if(A.front().first == 'D' && B.front().first == 'R'){
                        if(Ra - Rt <= x) ans++;
                    }
                }
            }
        }
        if(A.front().first == 'U') Rt -= x;
        if(A.front().first == 'D') Rt += x;
        if(A.front().first == 'L') Ct -= x;
        if(A.front().first == 'R') Ct += x;
        if(B.front().first == 'U') Ra -= x;
        if(B.front().first == 'D') Ra += x;
        if(B.front().first == 'L') Ca -= x;
        if(B.front().first == 'R') Ca += x;
        A.front().second -= x;
        B.front().second -= x;
        if(A.front().second == 0) A.pop();
        if(B.front().second == 0) B.pop();
    }
    cout << ans << endl;
}