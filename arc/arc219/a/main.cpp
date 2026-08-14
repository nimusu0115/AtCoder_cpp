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
ll pw(ll a,ll b){
    ll res = 1;
    while(b > 0){
        res *= a;
        b--;
    }
    return res;
}

int main() {
    int N,M;
    cin >> N >> M;
    vector<string> S(N);
    rep(i,N) cin >> S[i];

    sort(ALL(S));

    string ans = "";
    rep(i,M) ans = ans + '0';

    rep(i,N){
        bool flg = true;
        rep(j,M) if(ans[j] != S[i][j]) flg = false;
        if(!flg){
            cout << "Yes" << endl;
            rep(j,M){
                if(ans[j] == '0') cout << 1;
                else cout << 0;
            }
            cout << endl;
            return 0;
        }

        string plus = "";
        bool kuri = true;
        bool one = true;
        rrep(j,M){
            if(kuri){
                if(ans[j] == '0') ans[j] = '1',kuri = false;
                else ans[j] = '0';
            }
        }
    }

    if(M >= 20){
        cout << "Yes" << endl;
        rep(j,M) cout << '0';
        cout << endl;
        return 0;
    }
    else{
        if(pw(2,M) == N) cout << "No" << endl;
        else{
            cout << "Yes" << endl;
            rep(j,M) cout << '0';
            cout << endl;
        }
    }
}