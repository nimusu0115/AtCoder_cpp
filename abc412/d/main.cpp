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
    cin >> N >> M;

    vector<vector<int>> G(N,vector<int>{});
    rep(i,M){
        int a,b;
        cin >> a >> b;
        G[a - 1].push_back(b - 1);
        G[b - 1].push_back(a - 1);
    }

    set<vector<int>> S;
    S.insert({N});
    if(N == 6) S.insert({3,3});
    if(N == 7) S.insert({4,3});
    if(N == 8) S.insert({5,3}),S.insert({4,4});

    int ans = inf;
    vector<int> P(N);
    rep(i,N) P[i] = i;
    for(auto v : S){
        do{
            int minus = 0;
            int plus = 0;
            int m = 0;
            for(int i : v){
                rep(j,i){
                    bool flg = false;
                    for(int to : G[P[m + j]]){
                        if(j != 0 && j != i - 1){
                            if(to != P[m + j + 1] && to != P[m + j - 1]) minus++;
                            else if(to == P[m + j + 1]) flg = true;
                        }
                        else if(j == 0){
                            if(to != P[m + j + 1] && to != P[m + i - 1]) minus++;
                            else if(to == P[m + j + 1]) flg = true;
                        }
                        else if(j == i - 1){
                            if(to != P[m] && to != P[m + j - 1]) minus++;
                            else if(to == P[m]) flg = true;
                        }
                    }
                    if(!flg) plus++;
                }
                m += i;
            }
            chmin(ans,minus / 2 + plus);
        }while(next_permutation(ALL(P)));
    }

    cout << ans << endl;
}