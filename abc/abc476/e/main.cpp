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

int op_max(int a,int b){
    return max(a,b);
}

int op_min(int a,int b){
    return min(a,b);
}

int e_max(){
    return -inf;
}
int e_min(){
    return inf;
}

int main() {
    int N,M;
    cin >> N >> M;
    vector<int> P(N),rP(N);
    rep(i,N) cin >> P[i];
    rep(i,N) P[i]--;
    rep(i,N) rP[P[i]] = i; 

    segtree<int,op_max,e_max> seg_max(P);
    segtree<int,op_min,e_min> seg_min(P);

    while(M > 0){
        M--;

        int L,R;
        cin >> L >> R;
        L--,R--;

        int M = seg_max.prod(L,R + 1);
        int m = seg_min.prod(L,R + 1);

        seg_max.set(rP[M],m);
        seg_max.set(rP[m],M);
        seg_min.set(rP[M],m);
        seg_min.set(rP[m],M);

        swap(P[rP[M]],P[rP[m]]);
        swap(rP[M],rP[m]);

    }

    rep(i,N){
        cout << P[i] + 1;
        if(i != N - 1) cout << " ";
    }
    cout << endl;
}