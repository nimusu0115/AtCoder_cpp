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

    vector<int> A(N),D(N),B(N);
    rep(i,N) cin >> A[i] >> D[i] >> B[i];

    vector<tuple<int,int,int>> t(N);
    rep(i,N) t[i] = {D[i],A[i],B[i]};
    sort(ALL(t));

    rep(i,N){
        A[i] = get<1>(t[i]);
        D[i] = get<0>(t[i]);
        B[i] = get<2>(t[i]);
    }

    map<int,int> m;
    int clr = 0;
    rep(i,N) m[A[i] - 1]++;
    rep(i,N) if(m[i] > 0) clr++;

    int a = 0;
    onerep(i,M){
        bool flg = true;
        while(flg && a < N){
            if(D[a] == i){
                if(A[a] != B[a]){
                    m[A[a] - 1]--;
                    m[B[a] - 1]++;
                    if(m[A[a] - 1] == 0) clr--;
                    if(m[B[a] - 1] == 1) clr++;
                }
                a++;
            }
            else flg = false;
        }
        cout << clr << endl;
    }
}