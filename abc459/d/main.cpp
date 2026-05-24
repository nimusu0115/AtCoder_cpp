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
    int T;
    cin >> T;

    while(T > 0){
        T--;

        string S;
        cin >> S;

        vector<int> v(26,0);
        rep(i,S.size()){
            int a = S[i] - 'a';
            v[a]++;
        }

        int m = 0;
        rep(i,26) chmax(m,v[i]);

        if(m <= (S.size() + 1) / 2){
            cout << "Yes" << endl;

            set<pair<int,int>,greater<pair<int,int>>> ss;
            rep(i,26){
                if(v[i] != 0) ss.insert({v[i],i});
            }

            string ansl = "",ansr = "";

            bool flg = true;
            while(ss.size() > 1){
                if(flg){
                    auto k = *ss.begin();
                    char a = 'a' + k.second;
                    rep(i,k.first) ansl = ansl + a;
                }
                else{
                    auto k = *ss.begin();
                    char a = 'a' + k.second;
                    rep(i,k.first) ansr = a + ansr;
                }
                ss.erase(ss.begin());
                flg ^= 1;
            }
            auto k = *ss.begin();
            char a = 'a' + k.second;
            int t = (S.size() + 1) / 2 - ansl.size();
            rep(i,t) ansl = ansl + a;
            rep(i,k.first - t) ansr = a + ansr;
            //cout << k.first << " " << k.second << " " << t << endl;
            //cout << ss.size() << endl;

            rep(i,S.size()){
                if(i % 2 == 0) cout << ansl[i / 2];
                else cout << ansr[(i - 1) / 2];
            }
            cout << endl;
            //cout << ansl << " " << ansr << endl;
            //for(auto c : ss) cout << c.first << " " << c.second << endl;
        }
        else{
            cout << "No" << endl;
        }
    }
}