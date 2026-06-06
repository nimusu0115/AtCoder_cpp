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
vector<vector<int>> imos;
ll sum(int i,int j,int k,int l){
    return imos[k + 1][l + 1] - imos[k + 1][j] - imos[i][l + 1] + imos[i][j];
}

int main() {
    int H,W,K;
    cin >> H >> W >> K;
    vector<string> S(H);
    rep(i,H) cin >> S[i];

    imos.resize(1001,vector(1001,0));
    rep(i,H){
        rep(j,W){
            if(S[i][j] == '0') imos[i + 1][j + 1] = 0;
            else imos[i + 1][j + 1] = 1;
        }
    }
    
    rep(i,1001){
        rep(j,1001){
        if(j == 0)continue;
        imos[i][j] += imos[i][j - 1];
        }
    }
    
    rep(j,1001){
        rep(i,1001){
        if(i == 0) continue;
        imos[i][j] += imos[i - 1][j];
        }
    }

    /*rep(i,H + 1){
        rep(j,W + 1){
            cout << imos[i][j];
        }
        cout << endl;
    }*/

    ll ans = 0;
    rep(i,H){
        rep(j,W){
            int k = H - 1,l = j;
            vector<int> max(W,0),min(W,0);
            while(l < W){
                while(sum(i,j,k,l) > K && k > i){
                k--;
                }
                max[l] = k;
                l++;
            }
            k = H - 1,l = j;
            while(l < W){
                while(sum(i,j,k,l) >= K && k >= i){
                k--;
                }
                min[l] = k;
                l++;
            }

            for(int p = j;p < W;p++){
                if(sum(i,j,max[p],p) == K) ans += max[p] - min[p];
            }
            //if(i == 1 && j == 0) for(int p = j;p < W;p++) cout << min[p] << " " << max[p] << endl;
            //cout << ans;
        }
        //cout << endl;
    }

    cout << ans << endl;
}