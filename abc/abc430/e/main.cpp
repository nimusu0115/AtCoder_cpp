//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

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
    int T;
    cin >> T;
    while(T > 0){
        T--;

        string A,B;
        cin >> A >> B;

        string S = B + "#" + A + A;
        vector<int> Z = z_algorithm(S);

        int ans = -1;
        for(int i = A.size() + 1;i < 3 * A.size() + 1;i++){
            if(ans != -1) continue;
            if(Z[i] == A.size()) ans = i - A.size() - 1;
        }

        cout << ans << endl;
    }
}