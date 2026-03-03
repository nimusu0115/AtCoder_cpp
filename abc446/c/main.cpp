#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;
        
        int N,D;
        cin >> N >> D;
        vector<int> A(N),B(N);
        rep(i,N) cin >> A[i];
        rep(i,N) cin >> B[i];

        queue<pair<int,int>> egg;
        rep(i,N){
            egg.push({i,A[i]});
            int b = B[i];
            while(b > 0){
                if(egg.front().second < b){
                    b -= egg.front().second;
                    egg.pop();
                }
                else{
                    egg.front().second -= b;
                    b = 0;
                }
            }
            while(egg.front().first <= i - D){
                egg.pop();
            }
        }
        int ans = 0;
        while(!egg.empty()){
            ans += egg.front().second;
            egg.pop();
        }
        cout << ans << endl;
    }
}