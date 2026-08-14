#include<bits/stdc++.h>
using namespace std;
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

int main() {
    int T;
    cin >> T;
    while(T > 0){
        T--;

        int N;
        cin >> N;
        string S;
        cin >> S;

        vector<pair<char,int>> rle;
        rep(i,N){
            if(i == 0) rle.push_back({S[i],1});
            else{
                if(S[i] == S[i - 1]) rle.back().second++;
                else rle.push_back({S[i],1});
            }
        }
        
        int mostlong0 = 0;
        rep(i,rle.size()) if(rle[i].first == '0') mostlong0 = max(mostlong0,rle[i].second);
        bool yetlong0 = true;
        ll ans0 = 0;
        rep(i,rle.size()){
            if(rle[i].first == '1') ans0 += rle[i].second;
            else{
                if(rle[i].second != mostlong0) ans0 += 2 * rle[i].second;
                else{
                    if(yetlong0) yetlong0 = false;
                    else ans0 += 2 * rle[i].second;
                }
            }
        }

        int mostlong1 = 0;
        rep(i,rle.size()) if(rle[i].first == '1') mostlong1 = max(mostlong1,rle[i].second);
        bool yetlong1 = true;
        ll ans1 = 0;
        rep(i,rle.size()){
            if(rle[i].first == '0') ans1 += rle[i].second;
            else{
                if(rle[i].second != mostlong1) ans1 += 2 * rle[i].second;
                else{
                    if(yetlong1) yetlong1 = false;
                    else ans1 += 2 * rle[i].second;
                }
            }
        }

        cout << min(ans0,ans1) << endl;
    }
}