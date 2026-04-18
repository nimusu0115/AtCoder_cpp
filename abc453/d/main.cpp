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
const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const char udlr[4] = {'D','R','U','L'};
int H,W;
vector<string> S;
vector<vector<vector<bool>>> seen;
vector<vector<vector<tuple<int,int,int>>>> pre;
//到達可能性（グリッド）
void bfs_seen(pair<int,int> start){
    queue<tuple<int,int,int>> Q;
    rep(i,4){
        Q.push({start.first,start.second,i});
        seen[start.first][start.second][i] = true;
    }
    while(!Q.empty()){
        int h = get<0>(Q.front());
        int w = get<1>(Q.front());
        int dir = get<2>(Q.front());
        Q.pop();
        int nh = h + dx[dir];
        int nw = w + dy[dir];

        if(nh < 0 || H <= nh || nw < 0 || W <= nw) continue;
        if(S[nh][nw] == '#') continue;

        if(S[nh][nw] == '.') {
            rep(i,4){
                if(seen[nh][nw][i]) continue;
                Q.push({nh,nw,i});
                seen[nh][nw][i] = true;
                pre[nh][nw][i] = {h,w,i};
            }
        }
        if(S[nh][nw] == 'o'){
            if(seen[nh][nw][dir]) continue;
            Q.push({nh,nw,dir});
            seen[nh][nw][dir] = true;
            pre[nh][nw][dir] = {h,w,dir};
        }
        if(S[nh][nw] == 'x'){
            rep(i,4){
                if(i != dir){
                    if(seen[nh][nw][i]) continue;
                    Q.push({nh,nw,i});
                    seen[nh][nw][i] = true;
                    pre[nh][nw][i] = {h,w,i};
                }
            }
        }
        if(S[nh][nw] == 'G'){
            if(seen[nh][nw][dir]) continue;
            seen[nh][nw][dir] = true;
            pre[nh][nw][dir] = {h,w,dir};
        }
    }
}

int main() {
    cin >> H >> W;

    S.resize(H);
    rep(i,H) cin >> S[i];

    int sx,sy,gx,gy;
    rep(i,H) rep(j,W){
        if(S[i][j]  == 'S') sx = i,sy = j;
        if(S[i][j]  == 'G') gx = i,gy = j;
    }

    seen.resize(H,vector<vector<bool>>(W,vector<bool>(4,false)));
    pre.resize(H,vector<vector<tuple<int,int,int>>>(W,vector<tuple<int,int,int>>(4)));

    bfs_seen({sx,sy});

    rep(i,4){
        if(seen[gx][gy][i]){
            cout << "Yes" << endl;
            int posx = gx,posy = gy,posz = i;
            vector<char> ans;
            while(posx != sx || posy != sy){
                ans.push_back(udlr[get<2>(pre[posx][posy][posz])]);
                //cout << posx << posy << posz << pre[posx][posy][posz] << endl;
                int a = posz;
                posz = get<2>(pre[posx][posy][a]);
                posx = get<0>(pre[posx][posy][a]);
                posy = get<1>(pre[posx][posy][a]);
            }
            rrep(j,ans.size()) cout << ans[j];
            
            
            cout << endl;
            return 0;
        }
    }
    

    /*rep(i,H){
        rep(j,W){
            bool flg = false;
            rep(k,4) if(seen[i][j][k]) flg = true;
            cout << flg;
        }
        cout << endl;
    }*/
    cout << "No" << endl;
}