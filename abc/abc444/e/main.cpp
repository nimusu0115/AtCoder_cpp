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
    ll N,D;
    cin >> N >> D;

    vector<ll> A(N);
    rep(i,N) cin >> A[i];

    multiset<ll> S;
    S.insert(-llinf);
    S.insert(llinf);

    int right = 0;
    ll ans = 0;
    for(int left = 0;left < N;left++){
        while(right < N){
            ll up = *S.lower_bound(A[right]);
            ll dwn = *(--S.lower_bound(A[right]));
            if(up - A[right] >= D && A[right] - dwn >= D){
                S.insert(A[right]);
                right++;
            }
            else break;
        }
        ans += right - left;

        if(right == left){
            right++;
        }
        else{
            S.erase(A[left]);
        }
    }
    cout << ans << endl;
}