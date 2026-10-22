#include <bits/stdc++.h>
using namespace std;

// 更新のない配列の区間最小値。構築O(N log N)・空間O(N log N)、query O(1)。
// Tはminで比較できる型。空配列で構築可、queryは非空区間[l,r)のみ。
template<class T>
struct SparseTable {
    vector<vector<T>> table;
    vector<int> logarithm;
    explicit SparseTable(const vector<T>& values) {
        int n = static_cast<int>(values.size());
        logarithm.assign(n+1,0);
        for(int i = 2; i <= n; ++i) logarithm[i] = logarithm[i/2]+1;
        if(n == 0) return;
        table.push_back(values);
        for(int k = 1; (1LL<<k) <= n; ++k) {
            int count = n-(1<<k)+1;
            vector<T> row; row.reserve(count);
            for(int i = 0; i < count; ++i) row.push_back(min(table[k-1][i],table[k-1][i+(1<<(k-1))]));
            table.push_back(move(row));
        }
    }
    T query(int l,int r) const {
        assert(0 <= l && l < r && r < static_cast<int>(logarithm.size()));
        int k = logarithm[r-l];
        return min(table[k][l],table[k][r-(1<<k)]);
    }
};
