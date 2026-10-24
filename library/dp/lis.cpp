#include<bits/stdc++.h>
using namespace std;

// 最長増加部分列の長さ。strict=true: 狭義、false: 広義（同値を許す）。
// Tのoperator<は狭義弱順序。空列は0。O(N log(N+1))時間、O(N)空間。
// 復元用の親・添字配列は確保しない。
template<class T>
int lis_length(const vector<T>& A,bool strict = true){
    vector<T> tails;
    for(const T& value : A){
        auto it = tails.begin();
        if(strict) it = lower_bound(tails.begin(),tails.end(),value);
        else it = upper_bound(tails.begin(),tails.end(),value);
        if(it == tails.end()) tails.push_back(value);
        else *it = value;
    }
    return (int)tails.size();
}

// LISを構成する元配列の添字列を昇順で返す（値の列ではない）。
// 複数解のうち1つを返し、辞書順最小などは保証しない。空列は空配列。
// O(N log(N+1))時間、O(N)空間。使用例: for(int i : lis_indices(A)) cout << A[i];
template<class T>
vector<int> lis_indices(const vector<T>& A,bool strict = true){
    int N = (int)A.size();
    vector<T> tails;
    vector<int> tail_index,parent(N,-1);
    for(int i = 0;i < N;i++){
        auto it = tails.begin();
        if(strict) it = lower_bound(tails.begin(),tails.end(),A[i]);
        else it = upper_bound(tails.begin(),tails.end(),A[i]);
        int pos = (int)(it - tails.begin());
        if(pos > 0) parent[i] = tail_index[pos - 1];
        if(it == tails.end()){
            tails.push_back(A[i]);
            tail_index.push_back(i);
        }
        else{
            *it = A[i];
            tail_index[pos] = i;
        }
    }
    vector<int> res;
    if(tail_index.empty()) return res;
    for(int i = tail_index.back();i != -1;i = parent[i]) res.push_back(i);
    reverse(res.begin(),res.end());
    return res;
}
