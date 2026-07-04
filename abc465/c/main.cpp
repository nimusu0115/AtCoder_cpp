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
    int N;
    cin >> N;
    string S;
    cin >> S;

    vector<int> a,b;
    bool flg = true;
    rrep(i,N){
        if(S[i] == 'o'){
            if(flg) a.push_back(i + 1);
            else b.push_back(i + 1);
            flg ^= 1;
        }
        else{
            if(flg) b.push_back(i + 1);
            else a.push_back(i + 1);
        }
    }

    rep(i,a.size()){
        cout << a[i];
        if(i != a.size() - 1 || b.size() != 0) cout << " ";
    }
    rep(i,b.size()){
        cout << b[b.size() - 1 - i];
        if(i != b.size() - 1) cout << " ";
    }
    cout << endl;
}