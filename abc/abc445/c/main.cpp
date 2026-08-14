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
    int N;
    cin >> N;
    vector<int> A(N);
    rep(i,N) cin >> A[i];

    vector<vector<int>> G(N,vector<int>({}));
    rep(i,N) G[A[i] - 1].push_back(i);

    vector<int> seen(N,-1);

    rrep(i,N){
        if(seen[i] != -1) continue;
        queue<int> Q;
        Q.push(i);
        seen[i] = i;
        while(!Q.empty()){
            int pos = Q.front();
            Q.pop();
            for(int to : G[pos]){
              if(to == pos) continue;
                seen[to] = i;
                Q.push(to);
            }
        }
    }

    rep(i,N){
        cout << seen[i] + 1;
        if(i != N - 1) cout << " ";
    }
    cout << endl;

}