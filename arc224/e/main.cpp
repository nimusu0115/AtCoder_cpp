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

        string S;
        cin >> S;
        int N = S.size();

        stack<char> s;

        int f = 0;
        rrep(i,N){
            if(S[i] == 'A'){
                if(s.size() >= 2){
                    char b = s.top();
                    s.pop();
                    char c = s.top();
                    s.push(b);
                    if(b == 'B' && c == 'C'){
                        s.pop();
                        s.pop();
                    }
                    else if(b == 'B'){
                        s.pop();
                    }
                }
                else if(s.size() == 1){
                    char b = s.top();
                    if(b == 'B') s.pop();
                }
                //cout << s.size() << endl;
                continue;
            }
            s.push(S[i]);
            //cout << s.size() << endl;
        }

        cout << s.size() << endl;
        //cout << endl;
    }
}