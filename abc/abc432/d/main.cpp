#include<bits/stdc++.h>
#include <atcoder/all>
using namespace std;
using namespace atcoder;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 2'000'000'000;
const ll llinf = 3'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

struct Rect {
    long long l, r, d, u;
};

bool touch(const Rect& a, const Rect& b) {
    ll x_overlap = min(a.r, b.r) - max(a.l, b.l);
    ll y_overlap = min(a.u, b.u) - max(a.d, b.d);

    // 面積を持って重なる、または辺で接する
    return (x_overlap >= 0 && y_overlap > 0)
        || (x_overlap > 0 && y_overlap >= 0);
}

int main() {
    ll N,X,Y;
    cin >> N >> X >> Y;
    vector<Rect> S;
    S.push_back({0,X,0,Y});

    while(N > 0){
        N--;

        char C;
        ll A,B;
        cin >> C >> A >> B;

        vector<Rect> s;

        for(auto v : S){
            if(C == 'X'){
                if(v.r <= A){
                    s.push_back({v.l, v.r, v.d - B, v.u - B});
                }
                else if(A <= v.l){
                    s.push_back({v.l, v.r, v.d + B, v.u + B});
                }
                else{
                    s.push_back({v.l, A, v.d - B, v.u - B});
                    s.push_back({A, v.r, v.d + B, v.u + B});
                }
            }
            if(C == 'Y'){
                if(v.u <= A){
                    s.push_back({v.l - B, v.r - B, v.d, v.u});
                }
                else if(A <= v.d){
                    s.push_back({v.l + B, v.r + B, v.d, v.u});
                }
                else{
                    s.push_back({v.l - B, v.r - B, v.d, A});
                    s.push_back({v.l + B, v.r + B, A, v.u});
                }
            }
        }

        S = s;
    }

    int M = S.size();
    dsu uf(M);

    rep(i,M) rep(j,M) if(touch(S[i],S[j])) uf.merge(i,j);

    vector<vector<int>> G = uf.groups();

    vector<ll> masunokazu(G.size(),0);

    rep(i,G.size()){
        for(auto v : G[i]){
            masunokazu[i] += (S[v].r - S[v].l) * (S[v].u - S[v].d);
        }
    }

    sort(ALL(masunokazu));

    cout << masunokazu.size() << endl;
    rep(i,masunokazu.size()){
        cout << masunokazu[i];
        if(i != masunokazu.size() - 1) cout << " ";
    }

    cout << endl;
}