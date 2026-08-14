#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i = 0;i < n;i++)
#define rrep(i,n) for(ll i = n - 1;i >= 0;i--)
#define onerep(i,n) for(ll i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int main() {
    ll N,M;
    cin >> N >> M;
    vector<ll> L(M),R(M);
    rep(i,M) cin >> L[i] >> R[i];

    vector<pair<ll,ll>> LR(M),merged;
    rep(i,M) LR[i] = {L[i],R[i]};
    sort(ALL(LR));

    pair<ll,ll> cur;
    rep(i,M){
        if(i == 0){
            cur = LR[i];
            continue;
        }
        if(cur.second >= LR[i].first - 1){
            cur = {cur.first,LR[i].second};
        }
        else{
            merged.push_back(cur);
            cur = LR[i];
        }
    }
    merged.push_back(cur);

    ll day = 1;
    rep(i,merged.size()){
        if(merged[i].first - day >= N){
            cout << day + N - 1 << endl;
            return 0;
        }
        else{
            N -= merged[i].first - day;
            day = merged[i].second + 1;
        }
    }
    //for(auto s : merged) cout << s.first << " " << s.second << endl;
    cout << day + N - 1 << endl;
}