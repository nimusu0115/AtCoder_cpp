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
    int N,M;
    cin >> N;

    vector<int> A(N),B(N);
    rep(i,N) cin >> A[i] >> B[i];
    cin >> M;
    vector<string> S(M);
    rep(i,M) cin >> S[i];

    vector<map<char,bool>> X(N);
    rep(i,N){
        rep(j,M){
            if(A[i] == S[j].size()) X[i][S[j][B[i] - 1]] = true;
        }
    }

    rep(i,M){
        if(S[i].size() != N){
            cout << "No" << endl;
            continue;
        }
        bool flg = true;
        rep(j,N){
            if(!X[j][S[i][j]]) flg = false;
        }
        if(flg) cout << "Yes" << endl;
        else cout << "No" << endl;
    }

    //rep(i,N) cout << X[i][S[1][i]] << endl;
}