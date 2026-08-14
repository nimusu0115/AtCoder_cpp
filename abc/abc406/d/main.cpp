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
    int H,W,N;
    cin >> H >> W >> N;
    vector<int> X(N),Y(N);
    vector<set<int>> gyou(H),retu(W);
    rep(i,N){
        int x,y;
        cin >> x >> y;
        x--,y--;
        X[i] = x,Y[i] = y;
        gyou[x].insert(i);
        retu[y].insert(i);
    }

    int Q;
    cin >> Q;
    while(Q > 0){
        Q--;

        int c;
        cin >> c;
        if(c == 1){
            int x;
            cin >> x;
            x--;
            cout << gyou[x].size() << endl;
            while(!gyou[x].empty()){
                int a = *gyou[x].begin();
                gyou[x].erase(a);
                retu[Y[a]].erase(a);
            }
        }
        if(c == 2){
            int y;
            cin >> y;
            y--;
            cout << retu[y].size() << endl;
            while(!retu[y].empty()){
                int a = *retu[y].begin();
                retu[y].erase(a);
                gyou[X[a]].erase(a);
            }
        }
    }
}