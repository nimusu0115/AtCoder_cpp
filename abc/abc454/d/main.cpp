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
    int T;
    cin >> T;

    while(T > 0){
        T--;

        string A,B,Ares = "",Bres = "";
        cin >> A >> B;

        stack<char> a,b;

        rep(i,A.size()){
            a.push(A[i]);
            if(a.size() >= 4){
                string s = "";
                rep(j,4){
                    char c = a.top();
                    a.pop();
                    s = c + s;
                }
                if(s == "(xx)"){
                    a.push('x');
                    a.push('x');
                }
                else{
                    rep(j,4){
                        char c = s[j];
                        a.push(c);
                    }
                }
            }
        }
        while(!a.empty()){
            char c = a.top();
            a.pop();
            Ares = c + Ares;
        }

        rep(i,B.size()){
            b.push(B[i]);
            if(b.size() >= 4){
                string s = "";
                rep(j,4){
                    char c = b.top();
                    b.pop();
                    s = c + s;
                }
                if(s == "(xx)"){
                    b.push('x');
                    b.push('x');
                }
                else{
                    rep(j,4){
                        char c = s[j];
                        b.push(c);
                    }
                }
            }
        }
        while(!b.empty()){
            char c = b.top();
            b.pop();
            Bres = c + Bres;
        }

        if(Ares == Bres) cout << "Yes" << endl;
        else cout << "No" << endl;
    }
}