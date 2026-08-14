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
    ll N;
    cin >> N;
    string S;
    cin >> S;

    vector<ll> A_B(N + 1,0),B_C(N + 1,0),C_A(N + 1,0);
    vector<ll> sliceAB(2 * N + 1,0),sliceBC(2 * N + 1,0),sliceCA(2 * N + 1,0);
    vector<ll> AB_2C(N + 1,0);
    rep(i,N + 1){
    if(i == 0) continue;
        if(S[i - 1] == 'A'){
            A_B[i] = A_B[i - 1] + 1;
            B_C[i] = B_C[i - 1];
            C_A[i] = C_A[i - 1] - 1;
            AB_2C[i] = AB_2C[i - 1] + 1;
        }
        if(S[i - 1] == 'B'){
            A_B[i] = A_B[i - 1] - 1;
            B_C[i] = B_C[i - 1] + 1;
            C_A[i] = C_A[i - 1];
            AB_2C[i] = AB_2C[i - 1] + 1;
        }
        if(S[i - 1] == 'C'){
            A_B[i] = A_B[i - 1];
            B_C[i] = B_C[i - 1] - 1;
            C_A[i] = C_A[i - 1] + 1;
            AB_2C[i] = AB_2C[i - 1] - 2;
        }
    }

    map<pair<int,int>,ll> superslice;
    rep(i,N + 1){
        sliceAB[A_B[i] + N]++;
        sliceBC[B_C[i] + N]++;
        sliceCA[C_A[i] + N]++;
        superslice[{A_B[i],AB_2C[i]}]++;
    }

    ll slice = 0;
    rep(i,2 * N + 1){
        slice += sliceAB[i] * (sliceAB[i] - 1) / 2;
        slice += sliceBC[i] * (sliceBC[i] - 1) / 2;
        slice += sliceCA[i] * (sliceCA[i] - 1) / 2;
    }

    ll allslice = 0;
    for(auto v : superslice){
        allslice += v.second * (v.second - 1) / 2;
    }

    ll ans = N * (N + 1) / 2;
    ans -= slice;
    ans += 2 * allslice;

    cout << ans << endl;
    //cout << N * (N + 1) / 2 << endl;
    //cout << slice << endl;
    //cout << allslice << endl;
    //rep(i,2 * N + 1) cout << sliceAB[i] << endl;
    //onerep(i,N) cout << A_B[i] << endl;
}