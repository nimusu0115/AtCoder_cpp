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
    vector<vector<int>> A(N,vector<int>(N,inf));
    for(int i = 1;i <= N - 1;i++){
        for(int j = i + 1;j <= N;j++){
            int a;
            cin >> a;
            A[i - 1][j - 1] = a;
            A[j - 1][i - 1] = a;
        }
    }

    rep(i,N){
        rep(j,N){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
}