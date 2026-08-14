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
    int H,W;
    cin >> H >> W;

    vector<string> S(H);
    rep(i,H) cin >> S[i];

    vector<vector<int>> ans(H,vector<int>(W,inf)),aans(H,vector<int>(W,inf));

    ll cnt = 0;
    rep(i,H) rep(j,W) if(S[i][j] == '#') cnt++;
    if(cnt == H * W || cnt == 0){
        rep(i,H){
            rep(j,W){
                cout << '.';
            }
            cout << endl;
        }

        return 0;
    }

    rep(i,H){
        rep(j,W){
            if(S[i][j] == '.') ans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(ans[i][j],ans[i + a][j + b] + 1); 
            }
        }
    }

    rrep(i,H){
        rep(j,W){
            if(S[i][j] == '.') ans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(ans[i][j],ans[i + a][j + b] + 1); 
            }
        }
    }

    rep(j,W){
        rep(i,H){
            if(S[i][j] == '.') ans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(ans[i][j],ans[i + a][j + b] + 1); 
            }
        }
    }

    rrep(j,W){
        rep(i,H){
            if(S[i][j] == '.') ans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(ans[i][j],ans[i + a][j + b] + 1); 
            }
        }
    }

    //aans
    rep(i,H){
        rep(j,W){
            if(ans[i][j] % 2 == 1) aans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(aans[i][j],aans[i + a][j + b] + 1); 
            }
        }
    }

    rrep(i,H){
        rep(j,W){
            if(ans[i][j] % 2 == 1) aans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(aans[i][j],aans[i + a][j + b] + 1); 
            }
        }
    }

    rep(j,W){
        rep(i,H){
            if(ans[i][j] % 2 == 1) aans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(aans[i][j],aans[i + a][j + b] + 1); 
            }
        }
    }

    rrep(j,W){
        rep(i,H){
            if(ans[i][j] % 2 == 1) aans[i][j] = 0;
            rep(k,9){
                int a = k / 3 - 1;
                int b = k % 3 - 1;
                if(i + a >= 0 && i + a < H && j + b >= 0 && j + b < W) chmin(aans[i][j],aans[i + a][j + b] + 1); 
            }
        }
    }

    rep(i,H){
        rep(j,W){
            if(aans[i][j] % 2 == 0) cout << '#';
            else cout << '.';
        }
        cout << endl;
    }
}