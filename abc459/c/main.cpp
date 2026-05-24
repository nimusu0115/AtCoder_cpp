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
    int N,Q;
    cin >> N >> Q;

    multiset<int> S;
    rep(i,N) S.insert(0);
    vector<int> v(N,0);

    while(Q > 0){
        Q--;

        int c;
        int z;
        cin >> c >> z;

        if(c == 1){
            z--;
            S.erase(S.find(v[z]));
            v[z]++;
            S.insert(v[z]);
        }
        if(c == 2){
            int min = *S.begin();
            z += min;
            ll res = N - distance(S.begin(),S.lower_bound(z));
            cout << res << endl;
        }
        
    }
}