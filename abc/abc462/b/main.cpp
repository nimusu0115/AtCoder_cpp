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
    int N;
    cin >> N;
    vector<vector<int>> A(N);
    rep(i,N){
        int K;
        cin >> K;
        rep(j,K){
            int a;
            cin >> a;
            A[i].push_back(a - 1);
        }
    }

    vector<vector<int>> ans(N);
    rep(i,N){
        for(int a : A[i]) ans[a].push_back(i);
    }

    rep(i,N){
        cout << ans[i].size();
        for(int a : ans[i]) cout << " " << a + 1;
        cout << endl;
    }
}