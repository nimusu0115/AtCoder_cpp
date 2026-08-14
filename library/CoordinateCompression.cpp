#include<bits/stdc++.h>
using namespace std;

// 値の大小関係を保ったまま、0～種類数-1の連続した整数へ変換する座標圧縮。
template<class T>
struct CoordinateCompression{
    vector<T> values;

    // dataに含まれる値をソートし、重複を取り除いて前計算する。
    explicit CoordinateCompression(const vector<T>& data) : values(data){
        sort(values.begin(),values.end());
        values.erase(unique(values.begin(),values.end()),values.end());
    }

    // valueを圧縮した後の番号を返す。前提: valueはdataに含まれている。
    int get(const T& value) const{
        return static_cast<int>(lower_bound(values.begin(),values.end(),value) - values.begin());
    }

    // data全体を圧縮後の番号へ変換して返す。
    vector<int> compress(const vector<T>& data) const{
        vector<int> res;
        res.reserve(data.size());
        for(const T& value : data) res.push_back(get(value));
        return res;
    }

    // 圧縮後の番号 index に対応する元の値を返す。
    const T& value(int index) const{
        return values[index];
    }

    // 異なる値の種類数を返す。
    int size() const{
        return static_cast<int>(values.size());
    }
};
