// 実行例。提出時は必要な.cppだけをmainより前へ貼り付ける。
#include "../dp/lis.cpp"
#include "../dp/lcs.cpp"
#include "../dp/edit_distance.cpp"

int main(){
    vector<int> A = {3,1,2,2,4};
    assert(lis_length(A) == 3);
    assert(lis_length(A,false) == 4);
    vector<int> values;
    for(int i : lis_indices(A)) values.push_back(A[i]);
    assert((values == vector<int>{1,2,4}));

    string S = "abcde",T = "ace";
    assert(lcs_length(S,T) == 3);
    assert(lcs_restore(S,T) == "ace");
    assert(lcs_length(vector<int>{1,2,3},vector<int>{2,3,4}) == 2);

    assert(edit_distance(string("kitten"),string("sitting")) == 3);
    // 置換コストを3にすると、削除+挿入（計2）の方が安い。
    assert(edit_distance(string("a"),string("b"),1,1,3) == 2);
}
