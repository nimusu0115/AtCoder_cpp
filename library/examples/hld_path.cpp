// 実行例。提出時はinclude行の代わりに対象.cppを貼り付ける。
#include "../tree/hld.cpp"
#include <atcoder/segtree>

// 非可換演算の例: アフィン変換 f(x)=a*x+b のパス順合成。
// 各区間で正順と逆順を持つ。数値はこの例ではlong longに収まる範囲。
struct Affine { long long a,b; };
Affine then(Affine f,Affine g) { return {g.a*f.a,g.a*f.b+g.b}; }
struct Both { Affine forward,backward; };
Both op(Both x,Both y) { return {then(x.forward,y.forward),then(y.backward,x.backward)}; }
Both identity() { return {{1,0},{1,0}}; }

int main() {
    vector<vector<int>> g = {{1,2},{0},{0,3},{2}};
    HLD h(g);
    vector<Both> values(g.size());
    for(int v=0; v<static_cast<int>(g.size()); ++v) values[h.pos[v]]={{2,v},{2,v}};
    atcoder::segtree<Both,op,identity> seg(values);
    Affine result{1,0};
    for(auto s : h.path(1,3)) {
        auto value=seg.prod(s.l,s.r);
        result=then(result,s.reverse ? value.backward : value.forward);
    }
    // 頂点1->0->2->3: f3(f2(f0(f1(x)))) = 16x+15。
    assert(result.a==16 && result.b==15);
    // 辺重みなら子のposへ格納しh.path(u,v,true)、部分木はh.subtree(v,true)。
}
