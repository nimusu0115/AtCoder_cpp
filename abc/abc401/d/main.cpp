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
    ll N,K;
    cin >> N >> K;
    string S;
    cin >> S;

    vector<char> ans(N);

    rep(i,N - 1) if(S[i] == 'o') S[i + 1] = '.';
    rrep(i,N - 1) if(S[i + 1] == 'o') S[i] = '.';

    ll k = 0;
    rep(i,N) if(S[i] == 'o') k++;

    ll m = 0;
    ll cnt = 0;
    while(m < N){
        if(S[m] == '?'){
            ll a = 0;
            while(S[m] == '?' && m < N){
                a++;
                m++;
            }
            cnt += (a + 1) / 2;
        }
        else m++;
    }

    if(cnt + k == K){
        ll i = 0;
        while(i < N){
            if(S[i] != '?'){
                ans[i] = S[i];
                i++;
            }
            else{
                ll cnt = 0;
                while(S[cnt + i] == '?' && cnt + i < N) cnt++;
                if(cnt % 2 == 0){
                    rep(j,cnt) ans[i + j] = '?';
                }
                else{
                    rep(j,cnt){
                        if(j % 2 == 0) ans[i + j] = 'o';
                        else ans[i + j] = '.';
                    }
                }
                i += cnt;
            }
        }
        rep(x,N) cout << ans[x];
        cout << endl;
    }
    else cout << S << endl;
}