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
    vector<int> L(Q),R(Q),X(Q);
    rep(i,Q) cin >> L[i] >> R[i] >> X[i];

    vector<tuple<int,int,int>> t(Q);
    rep(i,Q){
        get<0>(t[i]) = X[i];
        get<1>(t[i]) = L[i];
        get<2>(t[i]) = R[i];
    }
    sort(ALL(t));
    rep(i,Q){
        X[i] = get<0>(t[i]);
        L[i] = get<1>(t[i]);
        R[i] = get<2>(t[i]);
    }

    multiset<pair<int,int>> S;

    rep(i,Q){
        if(i == 0) continue;
        if(X[i - 1] != X[i]){
            S.insert({L[i - 1],R[i - 1]});
            if(i == Q - 1) S.insert({L[i],R[i]});
            continue;
        }
        if(R[i - 1] <= L[i] - 2){
            S.insert({L[i - 1],R[i - 1]});
            if(i == Q - 1) S.insert({L[i],R[i]});
            continue;
        }
        if(R[i - 1] > R[i]){
            L[i] = L[i - 1];
            R[i] = R[i - 1];
            if(i == Q - 1) S.insert({L[i],R[i]});
            continue;
        }
        L[i] = L[i - 1];
        if(i == Q - 1) S.insert({L[i],R[i]});
    }

    vector<int> imos(N + 1,0);
    for(auto v : S){
        imos[v.first - 1]++;
        imos[v.second]--;
    }
    onerep(i,N) imos[i] += imos[i - 1];

    rep(i,N){
        cout << imos[i];
        if(i != N - 1) cout << " ";
    }
    cout << endl;

    //for(auto v : S) cout << v.first << " " << v.second << endl;
}