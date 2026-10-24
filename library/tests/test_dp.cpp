#include "../dp/lis.cpp"
#include "../dp/lcs.cpp"
#include "../dp/edit_distance.cpp"

template<class Sequence>
bool is_subsequence(const Sequence& small,const Sequence& large){
    int pos = 0;
    for(const auto& value : large){
        if(pos < (int)small.size() && small[pos] == value) pos++;
    }
    return pos == (int)small.size();
}

int brute_lis(const vector<int>& A,bool strict){
    int N = (int)A.size(),res = 0;
    for(int mask = 0;mask < (1 << N);mask++){
        int previous = -1,length = 0;
        bool ok = true;
        for(int i = 0;i < N;i++){
            if(!(mask >> i & 1)) continue;
            if(previous != -1){
                if(strict && A[previous] >= A[i]) ok = false;
                if(!strict && A[previous] > A[i]) ok = false;
            }
            previous = i;
            length++;
        }
        if(ok) res = max(res,length);
    }
    return res;
}

void check_lis(const vector<int>& A){
    for(bool strict : {true,false}){
        int want = brute_lis(A,strict);
        assert(lis_length(A,strict) == want);
        auto indices = lis_indices(A,strict);
        assert((int)indices.size() == want);
        for(int i = 0;i < (int)indices.size();i++){
            assert(0 <= indices[i] && indices[i] < (int)A.size());
            if(i == 0) continue;
            assert(indices[i - 1] < indices[i]);
            if(strict) assert(A[indices[i - 1]] < A[indices[i]]);
            else assert(A[indices[i - 1]] <= A[indices[i]]);
        }
    }
}

template<class Sequence>
int brute_lcs(const Sequence& A,const Sequence& B){
    int res = 0;
    for(int mask = 0;mask < (1 << (int)A.size());mask++){
        Sequence sub;
        for(int i = 0;i < (int)A.size();i++){
            if(mask >> i & 1) sub.push_back(A[i]);
        }
        if(is_subsequence(sub,B)) res = max(res,(int)sub.size());
    }
    return res;
}

template<class Sequence>
ll table_edit_distance(const Sequence& A,const Sequence& B,ll ins,ll del,ll replace){
    int N = (int)A.size(),M = (int)B.size();
    vector<vector<ll>> dp(N + 1,vector<ll>(M + 1));
    for(int i = 0;i <= N;i++) dp[i][0] = i * del;
    for(int j = 0;j <= M;j++) dp[0][j] = j * ins;
    for(int i = 1;i <= N;i++){
        for(int j = 1;j <= M;j++){
            ll cost = replace;
            if(A[i - 1] == B[j - 1]) cost = 0;
            dp[i][j] = min(dp[i - 1][j - 1] + cost,
                           min(dp[i - 1][j] + del,dp[i][j - 1] + ins));
        }
    }
    return dp[N][M];
}

template<class Sequence>
void check_lcs(const Sequence& A,const Sequence& B){
    int want = brute_lcs(A,B);
    assert(lcs_length(A,B) == want && lcs_length(B,A) == want);
    auto res = lcs_restore(A,B);
    assert((int)res.size() == want);
    assert(is_subsequence(res,A) && is_subsequence(res,B));
    res = lcs_restore(B,A);
    assert((int)res.size() == want);
    assert(is_subsequence(res,A) && is_subsequence(res,B));
}

// LISは比較だけでよく、デフォルト構築や等値比較を要求しない。
struct OrderedValue{
    int value;
    explicit OrderedValue(int x) : value(x){}
    bool operator<(const OrderedValue& other) const{
        return value < other.value;
    }
};

// LCS/編集距離は等値比較だけでよい。
struct EqualValue{
    int value;
    explicit EqualValue(int x) : value(x){}
    bool operator==(const EqualValue& other) const{
        return value == other.value;
    }
};

int main(){
    for(const vector<int>& A : vector<vector<int>>{{},{7},{1,2,3,4},{4,3,2,1},
                                                  {2,2,2},{3,1,2,2,4}}) check_lis(A);
    assert(lis_length(vector<int>{2,2,2}) == 1);
    assert(lis_length(vector<int>{2,2,2},false) == 3);
    vector<OrderedValue> ordered = {OrderedValue(2),OrderedValue(1),OrderedValue(1)};
    assert(lis_length(ordered) == 1 && lis_length(ordered,false) == 2);
    assert(lis_indices(ordered).size() == 1 && lis_indices(ordered,false).size() == 2);
    assert(lis_length(vector<string>{"b","a","c"}) == 2);
    assert(lis_length(vector<ll>{LLONG_MIN,0,LLONG_MAX}) == 3);

    for(const pair<string,string>& inputs : vector<pair<string,string>>{
            {"",""},{"","abc"},{"abc",""},{"abc","abc"},
            {"abc","XYZ"},{"abcbdab","bdcaba"},{"aaaa","aa"}}){
        check_lcs(inputs.first,inputs.second);
    }
    // 同点ではA側を先に捨てる規則を固定。
    assert(lcs_restore(string("ab"),string("ba")) == "a");
    vector<EqualValue> eq_a = {EqualValue(1),EqualValue(2)},eq_b = {EqualValue(2)};
    assert(lcs_length(eq_a,eq_b) == 1);
    assert(lcs_restore(eq_a,eq_b)[0].value == 2);
    assert(edit_distance(eq_a,eq_b) == 1);

    assert(edit_distance(string(),string()) == 0);
    assert(edit_distance(string("abc"),string("abc")) == 0);
    assert(edit_distance(string(),string("abc")) == 3);
    assert(edit_distance(string("abc"),string()) == 3);
    assert(edit_distance(string("abc"),string("xyz")) == 3);
    assert(edit_distance(string("kitten"),string("sitting")) == 3);
    assert(edit_distance(string("abc"),string("abxc")) == 1);
    assert(edit_distance(string("abxc"),string("abc")) == 1);
    assert(edit_distance(string("a"),string("b"),1,1,5) == 2);
    assert(edit_distance(string(),string("abc"),2,7,4) == 6);
    assert(edit_distance(string("abc"),string(),2,7,4) == 21);
    assert(edit_distance(string("a"),string("bbb"),0,0,0) == 0);
    assert(edit_distance(string("a"),string("b"),3000000000LL,3000000000LL,4000000000LL) == 4000000000LL);

    mt19937 rng(20261024);
    for(int trial = 0;trial < 500;trial++){
        int N = rng() % 11,M = rng() % 11;
        vector<int> A(N),B(M);
        string S,T;
        for(int& x : A){
            x = (int)(rng() % 5) - 2;
            S.push_back('a' + x + 2);
        }
        for(int& x : B){
            x = (int)(rng() % 5) - 2;
            T.push_back('a' + x + 2);
        }
        check_lis(A);
        check_lcs(A,B);
        check_lcs(S,T);
        assert(edit_distance(S,T) == table_edit_distance(S,T,1,1,1));
        for(int step = 0;step < 5;step++){
            ll ins = rng() % 5,del = rng() % 5,replace = rng() % 7;
            assert(edit_distance(A,B,ins,del,replace) == table_edit_distance(A,B,ins,del,replace));
            assert(edit_distance(B,A,ins,del,replace) == table_edit_distance(B,A,ins,del,replace));
        }
    }
    int large_size = 200000;
#ifdef _GLIBCXX_DEBUG
    // debug版のlower_boundは毎回区間全体を検査するので、検査用サイズを抑える。
    large_size = 2000;
#endif
    vector<int> large(large_size);
    iota(large.begin(),large.end(),0);
    assert(lis_length(large) == large_size && lis_indices(large).size() == large.size());
    reverse(large.begin(),large.end());
    assert(lis_length(large) == 1 && lis_indices(large).size() == 1);
    string long_string(200000,'a'),short_string(3,'a');
    assert(lcs_length(long_string,short_string) == 3);
    assert(lcs_length(short_string,long_string) == 3);
    assert(edit_distance(long_string,short_string) == 199997);
    assert(edit_distance(short_string,long_string) == 199997);
    cout << "DP: boundaries, generic types, 500 randomized cases, large/uneven inputs passed\n";
}
