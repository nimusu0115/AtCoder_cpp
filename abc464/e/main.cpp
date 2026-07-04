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
    int H,W,Q;
    cin >> H >> W >> Q;
    vector<int> R(Q),C(Q);
    vector<char> X(Q);
    rep(i,Q) cin >> R[i] >> C[i] >> X[i];
    rep(i,Q) R[i]--,C[i]--;

    vector<vector<int>> ans(H,vector<int>(W,0));
    rrep(i,Q){
        if(ans[R[i]][C[i]] > 0) continue;
        int k = R[i];
        while(k >= 0 && ans[k][C[i]] == 0){
            int l = C[i];
            while(l >= 0 && ans[k][l] == 0){
                ans[k][l] = i + 1;
                l--;
            }
            k--;
        }
    }

    rep(i,H){
        rep(j,W){
            if(ans[i][j] == 0) cout << 'A';
            else cout << X[ans[i][j] - 1];
        }
        cout << endl;
    }
}