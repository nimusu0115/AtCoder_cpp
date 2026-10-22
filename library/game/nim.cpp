#include<bits/stdc++.h>
using namespace std;
using ll = long long;
// a を現在値と b の大きい方／小さい方に更新する。

// 通常のNimで先手必勝なら true を返す。heaps[i]は各山の石の個数。
bool nim(const vector<ll>& heaps) {
    ll nim_sum = 0;
    for (ll count : heaps) {
        nim_sum ^= count;
    }

    return nim_sum != 0;
}

// 各手で1つの山から1～K個を取り除くNimで、先手必勝なら true を返す。
// 前提: K >= 1。
bool Knim(const vector<ll>& heaps,ll K) {
    assert(K >= 1);
    ll nim_sum = 0;
    for (ll count : heaps) {
        assert(count >= 0);
        nim_sum ^= static_cast<ll>(count % (static_cast<__int128>(K) + 1));
    }

    return nim_sum != 0;
}

// 関数を問題ごとに呼び出すためのエントリーポイント。

