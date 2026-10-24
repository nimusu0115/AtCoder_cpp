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

        map<char,int> m;

        for(char c : S) m[c]++;
        vector<pair<int,char>> V;
        for(auto v : m){
            V.push_back({v.second,v.first});
        }
        sort(ALL(V));
        reverse(ALL(V));

        string s = "";
        for(auto v : V){
            rep(i,v.first) s += v.second;
        }

        vector<char> ans(S.size());
        onerep(i,S.size()){
            int mid = (S.size() + 1) / 2;
            if(i <= mid) ans[(i - 1) * 2] = s[i - 1];
            else ans[(i - mid - 1) * 2 + 1] = s[i - 1];
        }

        bool flg = true;
        rep(i,S.size()){
            if(i == 0) continue;
            if(ans[i] == ans[i - 1]) flg = false;
        }
        if(flg){
            cout << "Yes" << endl;
            rep(i,S.size()) cout << ans[i];
            cout << endl;
        }
        else cout << "No" << endl;
    }
}