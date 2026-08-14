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
    int N,M;
    cin >> N >> M;
    vector<int> A(M),B(M);
    rep(i,M) cin >> A[i] >> B[i];

    int ans = 0;
    int a = A[0],c,d,cnt = 0,ccnt = 0,dcnt = 0;
    set<pair<int,int>> S;
    rep(i,M){
        if(A[i] == a || B[i] == a) continue;
        c = A[i],d = B[i];
    }
    rep(i,M){
        if(A[i] == a || B[i] == a) continue;
        cnt++;
        if(A[i] == c || B[i] == c) ccnt++;
        if(A[i] == d || B[i] == d) dcnt++;
    }
    if(cnt == ccnt && cnt != 0) S.insert({a,c}),S.insert({c,a});
    if(cnt == dcnt && cnt != 0) S.insert({a,d}),S.insert({d,a});

    int b = B[0],e,f,cnt2 = 0,ecnt = 0,fcnt = 0;
    rep(i,M){
        if(A[i] == b || B[i] == b) continue;
        e = A[i],f = B[i];
    }
    rep(i,M){
        if(A[i] == b || B[i] == b) continue;
        cnt2++;
        if(A[i] == e || B[i] == e) ecnt++;
        if(A[i] == f || B[i] == f) fcnt++;
    }
    if(cnt2 == ecnt && cnt2 != 0) S.insert({b,e}),S.insert({e,b});
    if(cnt2 == fcnt && cnt2 != 0) S.insert({b,f}),S.insert({f,b});

    if(cnt == 0 && cnt2 != 0) cout << N - 2 + S.size() / 2 << endl;
    else if(cnt != 0 && cnt2 == 0) cout << N - 2 + S.size() / 2 << endl;
    else if(cnt == 0 && cnt2 == 0) cout << 2 * (N - 2) + 1 << endl;
    else cout << S.size() / 2 << endl;
    //for(auto a : S) cout << a.first << a.second << endl;
}