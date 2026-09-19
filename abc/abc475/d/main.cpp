#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
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

ll pw(ll a,ll b){
    assert(b >= 0);
    ll res = 1;
    while(b > 0){
        if(b & 1) res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}

vector<int> enumerate_primes(int N) {
    vector<bool> is_prime(N + 1, true);

    if (N >= 0) is_prime[0] = false;
    if (N >= 1) is_prime[1] = false;

    for (int p = 2; 1LL * p * p <= N; p++) {
        if (!is_prime[p]) continue;

        for (long long x = 1LL * p * p; x <= N; x += p) {
            is_prime[x] = false;
        }
    }

    vector<int> primes;
    for (int x = 2; x <= N; x++) {
        if (is_prime[x]) primes.push_back(x);
    }

    return primes;
}

int main() {
    string S;
    cin >> S;
    int N = S.size();

    int n = pw(10,N - 1),m = pw(10,N);

    vector<int> PrimeTable = enumerate_primes(pw(10,7));

    for(int p : PrimeTable){
        if(p < n || m <= p) continue;
        map<char,int> m;
        bool flg = true;
        rep(i,N){
            int t = (p / pw(10,N - i - 1)) % 10;
            if(!m.count(S[i])){
                m[S[i]] = t;
            }
            else if(m[S[i]] != t) flg = false;
        }
        if(flg){
            cout << p << endl;
            return 0;
        }
    }

    cout << -1 << endl;
}