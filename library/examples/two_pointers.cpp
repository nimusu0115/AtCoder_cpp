#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// 非負配列Aで、区間和がK以下の空でない連続部分配列の個数を求める。
// 入力: N K、続いてAのN要素。計算量O(N)。
// 計算途中の和・答えもllの範囲内で使う。
int main(){
    int N;
    ll K;
    if(!(cin >> N >> K)) return 0;
    vector<ll> A(N);
    for(int i = 0;i < N;i++) cin >> A[i];

    // ここから尺取り法。区間[left,right)の和をsumで管理する。
    int right = 0;
    ll sum = 0;
    ll res = 0;
    for(int left = 0;left < N;left++){
        while(right < N && sum + A[right] <= K){
            sum += A[right];
            right++;
        }

        res += right - left;

        if(right == left){
            right++;
        }
        else{
            sum -= A[left];
        }
    }
    // ここまで。条件や答えの更新部分を問題に合わせて変更する。

    cout << res << endl;
}
