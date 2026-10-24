#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(ll i = 0;i < n;i++)
#define rrep(i,n) for(ll i = n - 1;i >= 0;i--)
#define onerep(i,n) for(ll i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1<<30;
const ll llinf = 1LL<<60;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

// オフライン区間加算。add O(1)、build O(N)、再度buildしても差分は壊さない。
// 差分・累積和の計算途中も含めてllの範囲内で使う。
struct Imos{
    vector<ll> difference;
    explicit Imos(int N) : difference(N + 1){
        assert(N >= 0);
    }
    void add(int l,int r,ll value){
        assert(0 <= l && l <= r && r < static_cast<int>(difference.size()));
        difference[l] += value;
        difference[r] -= value;
    }
    vector<ll> build() const{
        vector<ll> result(difference.size() - 1);
        ll current = 0;
        for(int i = 0;i < static_cast<int>(result.size());i++){
            current += difference[i];
            result[i] = current;
        }
        return result;
    }
};

int main() {
    ll N,D;
    cin >> N >> D;

    vector<ll> S(N),T(N);
    rep(i,N) cin >> S[i] >> T[i];

    Imos imos(1'000'000);
    rep(i,N){
        if(T[i] - S[i] < D) continue;
        imos.add(S[i],T[i] - D + 1,1);
    }
    vector<ll> bld = imos.build();

    ll ans = 0;
    rep(i,bld.size()) ans += bld[i] * (bld[i] - 1) / 2;

    cout << ans << endl;
}