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
        int L;
        cin >> L;
        rep(j,L){
            int a;
            cin >> a;
            A[i].push_back(a);
        }
    }
    int X,Y;
    cin >> X >> Y;
    cout << A[X - 1][Y - 1] << endl;
}