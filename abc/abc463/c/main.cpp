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

    vector<ll> H(N),L(N);
    rep(i,N) cin >> H[i] >> L[i];

    vector<pair<ll,ll>> LH(N),LmaxH(N + 1);
    rep(i,N) LH[i] = {L[i],H[i]};
    sort(ALL(LH));

    multiset<ll> s;
    rep(i,N) s.insert(H[i]);
    s.insert(0);

    LmaxH[0] = {0,*--s.end()};

    rep(i,N){
        s.erase(s.find(LH[i].second));
        LmaxH[i + 1] = {LH[i].first,*--s.end()};
    }

    int Q;
    cin >> Q;
    while(Q > 0){
        Q--;

        ll T;
        cin >> T;

        auto itr = lower_bound(ALL(LmaxH),make_pair(T,llinf));
        cout << (*--itr).second << endl;
    }
}