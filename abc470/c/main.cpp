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
    set<int> S;
    vector<int> A(N,0);
    int ans = 0;
    while(Q > 0){
        Q--;

        int c = 0;
        cin >> c;
        if(c == 1){
            int x;
            cin >> x;
            A[x - 1]++;
            S.insert(x - 1);
            ans = ans ^ (A[x - 1] - 1) ^ A[x - 1];
        }
        if(c == 2){
            set s = S;
            for(auto v : S){
                ans = ans ^ (A[v] - 1) ^ A[v];
                A[v]--;
                if(A[v] == 0) s.erase(v);
            }
            S = s;
        }
        //rep(i,N) cout << A[i];
        //cout << endl;
        cout << ans << endl;
    }
}