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
    int N,M;
    cin >> N >> M;
    vector<int> L(M),R(M);
    rep(i,M) cin >> L[i] >> R[i];

    vector<pair<int,int>> RL(M);
    rep(i,M) RL[i] = {R[i],L[i]};
    
    sort(ALL(RL));

    vector<bool> tyusya(N,false);
    int car = 0;
    rep(i,M){
        bool flg = false;
        rep(j,RL[i].first - RL[i].second + 1){
            if(!tyusya[RL[i].second + j - 1]){
                tyusya[RL[i].second + j - 1] = true;
                break;
            }
            if(j == RL[i].first - RL[i].second) flg = true;
        }
        if(flg){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
}