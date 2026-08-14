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

    vector<string> S(N);

    rep(i,N){
        cin >> S[i];
    }

    rep(i,N){
        if(S[i][0] - 'a' <= 2) cout << 2;
        else if(S[i][0] - 'a' <= 5) cout << 3;
        else if(S[i][0] - 'a' <= 8) cout << 4;
        else if(S[i][0] - 'a' <= 11) cout << 5;
        else if(S[i][0] - 'a' <= 14) cout << 6;
        else if(S[i][0] - 'a' <= 18) cout << 7;
        else if(S[i][0] - 'a' <= 21) cout << 8;
        else if(S[i][0] - 'a' <= 25) cout << 9;
    }
    
    cout << endl;
}