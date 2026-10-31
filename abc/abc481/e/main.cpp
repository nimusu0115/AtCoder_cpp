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

// |x|,|y| <= 10^18 を想定（外積は符号付き128bit内）。
// 原点から見た2次元ベクトル。cmpを使うと偏角の昇順に並べられる。
struct angsort{
  ll x;
  ll y;
};

// p と q の外積を返す。符号から反時計回り／時計回りの位置関係を判定できる。
// long long 同士の積であふれないよう、計算結果は __int128 とする。
__int128 cross(const angsort& p,const angsort& q){
  return (__int128)p.x * q.y - (__int128)q.x * p.y;
}

// ベクトルを上半平面(0)と下半平面(1)に分類する。ゼロベクトルだけは -1。
int half(const angsort& p){
  if(p.x == 0 && p.y == 0) return -1;
  return (p.y > 0 || (p.y == 0 && p.x >= 0)) ? 0 : 1;
}

// 原点を中心とした偏角で比較する関数。sortの第3引数として使用する。
// ゼロベクトルを先頭とし、正のx軸から反時計回りに並べる。
bool cmp(const angsort& p,const angsort& q){
  if(half(p) != half(q)) return half(p) < half(q);
  return cross(p,q) > 0;
}

// p と q が原点から同じ向きに伸びているかを返す。長さは一致しなくてもよい。
bool eql(const angsort& p,const angsort& q){
  return half(p) == half(q) && cross(p,q) == 0;
}

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        int N;
        cin >> N;
        vector<ll> X(N),Y(N);
        rep(i,N) cin >> X[i] >> Y[i];

        set<pair<ll,ll>> U,D;
        vector<angsort> V;
        rep(i,N){
            angsort a;
            a.x = X[i];
            a.y = Y[i];
            if(half(a)){
                U.insert({X[i],Y[i]});
                V.push_back(a);
            }
            else{
                a.x *= -1;
                a.y *= -1;
                D.insert({X[i],Y[i]});
                V.push_back(a);
            }
        }

        sort(ALL(V),cmp);

        int cnt = D.size();
        int ans = abs(cnt);
        rep(i,N){
            ll x = V[i].x;
            ll y = V[i].y;
            if(U.count({x,y})) cnt++;
            else cnt--;

            //cout << i << " " << cnt << endl;
            chmax(ans,max(abs(cnt),N - abs(cnt)));
        }

        cout << ans << endl;
    }
}