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
    ll N,M,C;
    cin >> N >> M >> C;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];

    sort(ALL(A));

    vector<ll> dis,ppl;
    rep(i,N){
        if(i == 0){
            dis.push_back(M - A.back() + A[i]);
            ppl.push_back(1);
            continue;
        }

        if(A[i] == A[i - 1]){
            ppl.back()++;
        }
        else{
            dis.push_back(A[i] - A[i - 1]);
            ppl.push_back(1);
        }
    }

    vector<ll> ppl2(ppl.size() * 2);
    rep(i,ppl.size()){
        ppl2[i] = ppl[i];
        ppl2[i + ppl.size()] = ppl[i];
    }
    vector<int> R(ppl.size(),0),X(ppl.size());
    ll m = ppl[0];
    rep(i,ppl.size()){
        if(i != 0){
            R[i] = R[i - 1];
            m -= ppl[i - 1];
        }
        while(m < C){
            R[i]++;
            m += ppl2[R[i]];
        }
        X[i] = m;
    }

    ll ans = 0;
    rep(i,ppl.size()) ans += dis[i] * X[i];
    cout << ans << endl;

}