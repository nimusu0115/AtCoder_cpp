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
    string S,T;
    cin >> S >> T;

    int s = 0,t = 0,ans = 0;
    while(s < S.size() && t < T.size()){
        if(S[s] == T[t]){
            s++;
            t++;
        }
        else if(S[s] == 'A'){
            s++;
            ans++;
        }
        else if(T[t] == 'A'){
            t++;
            ans++;
        }
        else{
            cout << -1 << endl;
            return 0;
        }
    }

    if(s >= S.size()){
        while(t < T.size()){
            if(T[t] == 'A'){
                t++;
                ans++;
            }
            else{
                cout << -1 << endl;
                return 0;
            }
        }
    }
    if(t >= T.size()){
        while(s < S.size()){
            if(S[s] == 'A'){
                s++;
                ans++;
            }
            else{
                cout << -1 << endl;
                return 0;
            }
        }
    }

    cout << ans << endl;
}