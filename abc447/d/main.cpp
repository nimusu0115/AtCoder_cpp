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

    int N = S.size();
    int a = 0,b = 0,c = 0;
    rep(i,N){
        if(S[i] == 'A') a++;
        else if(S[i] == 'B'){
            if(b < a) b++;
        }
        else if(S[i] == 'C'){
            if(c < b) c++;
        }
    }


    cout << c << endl;
}