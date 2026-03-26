#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define rep(i,n) for(int i = 0;i < n;i++)
#define rrep(i,n) for(int i = n - 1;i >= 0;i--)
#define onerep(i,n) for(int i = 1;i <= n;i++)
#define ALL(a)  (a).begin(),(a).end()
const int inf = 1'000'000'000;
const ll llinf = 2'000'000'000'000'000'000LL;
const double PI = 3.141592653589;
template<class T> void chmax(T& a,T b){ if(a < b) a = b;}
template<class T> void chmin(T& a,T b){ if(a > b) a = b;}

int main() {
    string X,Y;
    cin >> X >> Y;
    int q;
    cin >> q;

    map<char,ll> cX,cY;
    for(auto c : X) cX[c]++;
    for(auto c : Y) cY[c]++;

    vector<ll> length;
    ll a = X.size(),b = Y.size();
    length.push_back(a);
    length.push_back(b);
    while(b <= llinf){
        length.push_back(a + b);
        b += a;
        a = b - a;
    }

    while(q > 0){
        q--;

        ll L,R;
        char C;
        cin >> L >> R >> C;

        vector<ll> bunkai(length.size(),0);

        queue<tuple<int,ll,ll>> Q;
        auto itr = lower_bound(ALL(length),R);
        int start = distance(length.begin(),itr);

        Q.push({start,L,R});

        ll ans = 0;
        while(!Q.empty()){
            int n = get<0>(Q.front());
            ll l = get<1>(Q.front());
            ll r = get<2>(Q.front());
            Q.pop();

            if(n == 0){
                for(int i = l;i <= r;i++){
                    if(X[i] == C) ans++;
                }
            }
            else if(n == 1){
                for(int i = l;i <= r;i++){
                    if(Y[i] == C) ans++;
                }
            }
            else{
                if(l == 1){
                    if(r == length[n]){
                        bunkai[n - 1]++;
                        bunkai[n - 2]++;
                    }
                    if(length[n - 1] < r && r < length[n]){
                        bunkai[n - 1]++;
                        Q.push({n - 2,1,r - length[n - 1]});
                    }
                    if(r == length[n - 1]){
                        bunkai[n - 1]++;
                    }
                    if(r < length[n - 1]){
                        Q.push({n - 1,1,r});
                    }
                }
                if(1 < l && l < length[n - 1] + 1){
                    if(r == length[n]){
                        Q.push({n - 1,l,length[n - 1]});
                        bunkai[n - 2]++;
                    }
                    if(length[n - 1] < r && r < length[n]){
                        Q.push({n - 1,l,length[n - 1]});
                        Q.push({n - 2,1,r - length[n - 1]});
                    }
                    if(r == length[n - 1]){
                        Q.push({n - 1,l,length[n - 1]});
                    }
                    if(r < length[n - 1]){
                        Q.push({n - 1,l,r});
                    }
                }
                if(l == length[n - 1] + 1){
                    if(r == length[n]){
                        bunkai[n - 2]++;
                    }
                    if(r < length[n]){
                        Q.push({n - 2,1,r - length[n - 1]});
                    }
                }
                if(length[n - 1] + 1 < l){
                    Q.push({n - 2,l - length[n - 1],r - length[n - 1]});
                }
            }
        }
        rrep(i,length.size()){
            if(i <= 1) continue;
            bunkai[i - 1] += bunkai[i];
            bunkai[i - 2] += bunkai[i];
        }
        ans += bunkai[0] * cX[C];
        ans += bunkai[1] * cY[C];

        cout << ans << endl;
        //rep(i,start) cout << bunkai[i] << endl;
        //cout << start << endl;
    }
    //for(auto v : length) cout << v << endl;
}