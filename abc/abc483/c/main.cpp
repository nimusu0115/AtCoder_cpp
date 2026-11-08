//Library source:
//https://github.com/nimusu0115/AtCoder_cpp

#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
using mint = modint998244353;
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

int main() {
    int N,M;
    cin >> N >> M;
    vector<int> A(M),B(M);
    rep(i,M) cin >> A[i] >> B[i];
    rep(i,M) A[i]--,B[i]--;

    vector<pair<int,int>> P(M);
    rep(i,M) P[i] = {A[i],B[i]};
    sort(ALL(P));
    rep(i,M){
        A[i] = P[i].first;
        B[i] = P[i].second;
    }

    vector<int> num(N);
    rep(i,M) num[A[i]]++;
    int max = 0,max_ind = 0;
    rep(i,N) if(num[i] > max){
        max = num[i];
        max_ind = i;
    }

    map<int,map<int,int>> m;
    rep(i,M){
        m[A[i]][B[i]]++;
    }

    rep(i,N){
        if(i == max_ind){
            vector<int> nn(N);
            rep(j,M){
                if(A[j] == max_ind) nn[B[j]]++;
                else nn[A[j]]++;
            }

            int ans = 0,max_nn = 0;
            rep(j,N){
                if(nn[j] > max_nn){
                    max_nn = nn[j];
                    ans = j;
                }
            }
            //rep(j,N) cout << nn[j] << endl;
            cout << ans + 1 << endl;
        }else{
            int Max = max + m[i][max_ind];
            int ans = max_ind;
            for(auto v : m[i]){
                if(v.first == max_ind) continue;
                if(Max < num[v.first] + v.second){
                    Max = num[v.first] + v.second;
                    ans = v.first;
                }
                else if(Max == num[v.first] + v.second){
                    if(ans > v.first) ans = v.first;
                }
            }
            cout << ans + 1 << endl;
        }
    }
}