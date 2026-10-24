#include<bits/stdc++.h>
using namespace std;
using ll = long long;

// AをBへ変えるLevenshtein距離。string/vector<T>に対応、要素はoperator==で比較。
// 挿入・削除・置換のコスト（既定はすべて1）は非負。途中の計算もll内で使う。
// O(NM)時間、O(min(N,M))補助空間。空列は必要な挿入/削除のコストを返す。
// 使用例: edit_distance(string("kitten"),string("sitting")) == 3
template<class Sequence>
ll edit_distance(const Sequence& A,const Sequence& B,
                 ll insert_cost = 1,ll delete_cost = 1,ll replace_cost = 1){
    assert(insert_cost >= 0 && delete_cost >= 0 && replace_cost >= 0);
    // 向きを逆にすると挿入と削除も逆になる。
    if(A.size() < B.size()) return edit_distance(B,A,delete_cost,insert_cost,replace_cost);
    int N = (int)A.size(),M = (int)B.size();
    if(M == 0) return (ll)N * delete_cost;
    vector<ll> dp(M + 1);
    for(int j = 0;j <= M;j++) dp[j] = (ll)j * insert_cost;
    for(int i = 0;i < N;i++){
        ll diagonal = dp[0];
        dp[0] = (ll)(i + 1) * delete_cost;
        for(int j = 0;j < M;j++){
            ll previous = dp[j + 1];
            ll cost = 0;
            if(!(A[i] == B[j])) cost = replace_cost;
            dp[j + 1] = min(diagonal + cost,min(dp[j] + insert_cost,previous + delete_cost));
            diagonal = previous;
        }
    }
    return dp[M];
}
