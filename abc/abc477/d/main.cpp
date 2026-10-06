#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
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
    int N,Q;
    cin >> N >> Q;
    char clr = 'a';

    map<int,char> m;
    set<int> s;
    while(Q > 0){
        Q--;

        int t;
        cin >> t;
        if(t == 1){
            int x;
            cin >> x;
            x--;

            if(m.count(x)){
                if(s.count(x)) s.erase(x);
                else s.insert(x);
            }
            else m[x] = clr;
        }
        if(t == 2){
            char c;
            cin >> c;

            for(auto v : s) m.erase(v);
            s.clear();
            clr = c;
        }
    }

    rep(i,N){
        if(m.count(i)) cout << m[i];
        else cout << clr;
    }
    cout << endl;
}