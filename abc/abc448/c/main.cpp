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
    int N,Q;
    cin >> N >> Q;
    vector<ll> A(N);
    rep(i,N) cin >> A[i];
    vector<pair<ll,int>> Ai(N);
    rep(i,N) Ai[i] = {A[i],i};
    sort(ALL(Ai));
    vector<int> rA(N);
    rep(i,N) rA[Ai[i].second] = i;

    while(Q > 0){
        Q--;

        int K;
        cin >> K;
        vector<int> B(K);
        rep(i,K) cin >> B[i];
        bool flg = true;
        int a = 0;
        while(flg){
            bool flg2 = true;
            rep(i,K) if(a == rA[B[i] - 1]) flg2 = false;
            if(flg2){
                cout << Ai[a].first << endl;
                flg = false;
            }
            a++;
        }
    }
}