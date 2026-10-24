#include<bits/stdc++.h>
using namespace std;

// 最長共通部分列の長さ。Sequenceはstringまたはvector<T>、要素にoperator==が必要。
// O(NM)時間、O(min(N,M))補助空間。空列を含む場合は0。
template<class Sequence>
int lcs_length(const Sequence& A,const Sequence& B){
    if(A.size() < B.size()) return lcs_length(B,A);
    int N = (int)A.size(),M = (int)B.size();
    if(M == 0) return 0;
    vector<int> dp(M + 1);
    for(int i = 0;i < N;i++){
        int diagonal = 0;
        for(int j = 0;j < M;j++){
            int previous = dp[j + 1];
            if(A[i] == B[j]) dp[j + 1] = diagonal + 1;
            else dp[j + 1] = max(dp[j + 1],dp[j]);
            diagonal = previous;
        }
    }
    return dp[M];
}

// 実際のLCS（値の列）を入力と同じ型で返す。空列を含む場合は空列。
// O(NM)時間、O((N+1)(M+1))空間。復元の同点時はA側の末尾を先に捨てる。
template<class Sequence>
Sequence lcs_restore(const Sequence& A,const Sequence& B){
    int N = (int)A.size(),M = (int)B.size();
    if(N == 0 || M == 0) return {};
    vector<vector<int>> dp(N + 1,vector<int>(M + 1));
    for(int i = 0;i < N;i++){
        for(int j = 0;j < M;j++){
            if(A[i] == B[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
            else dp[i + 1][j + 1] = max(dp[i][j + 1],dp[i + 1][j]);
        }
    }
    Sequence res;
    int i = N,j = M;
    while(i > 0 && j > 0){
        if(A[i - 1] == B[j - 1]){
            res.push_back(A[i - 1]);
            i--;
            j--;
        }
        else if(dp[i - 1][j] >= dp[i][j - 1]) i--;
        else j--;
    }
    reverse(res.begin(),res.end());
    return res;
}
