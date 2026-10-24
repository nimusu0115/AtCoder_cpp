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

int op(int a,int b){
    return a + b;
}

int e(){
    return 0;
}

int main() {
    int N,Q,M;
    cin >> N >> Q;

    M = 1'000'000;
    vector<int> cnt(N,0);
    segtree<int,op,e> seg(M);
    seg.set(0,N);
    int base = 0;

    while(Q > 0){
        Q--;

        int c;
        int z;
        cin >> c >> z;
        z--;

        if(c == 1){
            seg.set(cnt[z],seg.get(cnt[z]) - 1);
            cnt[z]++;
            seg.set(cnt[z],seg.get(cnt[z]) + 1);
            
            if(seg.get(base) == 0) base++;
        }
        if(c == 2){
            cout << seg.prod(z + 1 + base,M) << endl;
        }
        
    }
}