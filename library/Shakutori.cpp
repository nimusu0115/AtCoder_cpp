#include<bits/stdc++.h>
using namespace std;
#define ll long long

// すべての要素が非負の配列について、総和がK以下となる連続部分配列の個数を返す。
// 左端と右端をそれぞれ一方向に動かすため、計算量は O(N)。
ll count_subarrays_sum_at_most(const vector<ll>& A,ll K){
    int N = static_cast<int>(A.size());
    int right = 0;
    ll sum = 0;
    ll res = 0;

    for(int left = 0;left < N;left++){
        while(right < N && sum + A[right] <= K){
            sum += A[right];
            right++;
        }

        // 右端を left～right-1 とする区間が条件を満たす。
        res += right - left;

        if(right == left){
            // A[left]単体でも条件を満たさない場合は、両端を次へ進める。
            right++;
        }
        else{
            sum -= A[left];
        }
    }
    return res;
}

// すべての要素が非負の配列について、総和がK以上となる最短の連続部分配列長を返す。
// 条件を満たす区間が存在しない場合は -1。計算量は O(N)。
int min_subarray_length_sum_at_least(const vector<ll>& A,ll K){
    int N = static_cast<int>(A.size());
    int left = 0;
    int res = N + 1;
    ll sum = 0;

    for(int right = 0;right < N;right++){
        sum += A[right];

        while(left <= right && sum >= K){
            res = min(res,right - left + 1);
            sum -= A[left];
            left++;
        }
    }

    if(res == N + 1) return -1;
    return res;
}

// 異なる値がK種類以下となる、最長の連続部分配列長を返す。
// 要素の大小や符号には制限がない。計算量は O(N log N)。
template<class T>
int longest_subarray_at_most_k_distinct(const vector<T>& A,int K){
    if(K < 0) return 0;

    int N = static_cast<int>(A.size());
    int left = 0;
    int res = 0;
    map<T,int> count;

    for(int right = 0;right < N;right++){
        count[A[right]]++;

        while(static_cast<int>(count.size()) > K){
            count[A[left]]--;
            if(count[A[left]] == 0) count.erase(A[left]);
            left++;
        }

        res = max(res,right - left + 1);
    }
    return res;
}
