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
    ll X;
    cin >> X;
    int Q;
    cin >> Q;

    multiset<ll> s;

    s.insert(X);
    auto med = s.begin();

    while(Q > 0){
        Q--;

        ll A,B;
        cin >> A >> B;

        s.insert(A);
        s.insert(B);

        if((A <= *med && *med <= B) || (B <= *med && *med <= A)){
            cout << *med;
        }
        else if(*med < A && *med < B){
            med++;
            cout << *med;
        }
        else if(*med > A && *med > B){
            med--;
            cout << *med;
        }
        cout << endl;
    }
}