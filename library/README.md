# AtCoder C++17 コピー用ライブラリ

必要な `.cpp` の内容を提出コードの `main()` より前へ貼り付ける。自作ヘッダ・バンドル処理は不要。
本体には `main()`・入力処理・可変グローバル状態・マクロを置かない。
`#include <bits/stdc++.h>` と `__int128` を使うのでGNU C++17以降を想定する。

- 頂点・配列は **0-indexed**、区間は **半開区間 `[l,r)`**。
- グラフは隣接リスト。無向辺は両側へ追加する。頂点番号は有効範囲内に限る。
- 木は連結無向木。空木の構築は可能だが、頂点を指定するクエリは非空木のみ。
- `assert` は前提条件の確認用。制約外入力を安全に処理する保証はない。NDEBUGで外れるため、呼び出し側でも条件を確認する。
- 戻り値が `long long` の和・積はその範囲に収める。中間値の128bit化は、任意精度の保証ではない。
- 各ファイルは単体で利用可能。ファイル内の補助型が必要な場合は下表に記載。
- [旧22ファイルの調査・新旧API対応](MIGRATION.md)、[検証結果・未実装項目](VALIDATION.md)。

```text
library/
  graph/           探索・最短路・SCC・DAG・最小全域森・Lowlink
  tree/            基本情報・直径・LCA・Euler Tour・HLD・全方位木DP
  data_structure/  UF・重み付きUF・Fenwick・RMQ・Sparse Table
  math/            篩・累乗・逆元・拡張GCD・二項係数・桁操作
  string/          Manacher・ACL Z-algorithm
  geometry/        偏角・軸平行矩形/直方体
  dp/              問題固有の桁DP例
  techniques/      圧縮・尺取り・累積和・いもす
  game/            Nim
  examples/        main付き実行例（提出時は本体を貼り付ける）
  tests/           再現可能なランダム/境界/大規模テスト
```

## グラフ

`n=頂点数、m=辺数`。`g` は `vector<vector<int>>`、`wg` は下表の重み付き隣接リスト。
空グラフの探索は空配列を返す（この場合のみ始点は参照しない）。

| ファイル / 用途 | API・入力 → 結果 | 時間 / 空間 | 条件・使用例 |
|---|---|---|---|
| [bfs.cpp](graph/bfs.cpp) / 無重み最短路・到達判定 | `bfs(g,s)` → `vector<int>`距離、未到達-1 | O(n+m) / O(n) | 有向/無向可。`auto d=bfs(g,0); bool reachable=d[v]!=-1;` |
| 同上 / 4近傍グリッド | `grid_bfs(vector<string>,{y,x},wall='#')` → 2D距離 | O(HW) / O(HW) | 長方形。壁/範囲外の始点なら全-1。`auto d=grid_bfs({"..","#."},{0,0});` |
| [dfs.cpp](graph/dfs.cpp) / 到達・探索木・入出時刻 | `dfs(g,s)` → `DFSResult` | O(n+m) / O(n) | `.parent/.depth/.tin/.tout`は未到達-1。`.preorder/.postorder`は頂点列。根の親-1、深さ0。`auto r=dfs(g,0);` |
| [shortest_path.cpp](graph/shortest_path.cpp) / Dijkstra | `dijkstra(wg,s)` → `vector<long long>`距離 | O((n+m)log(m+2)) / O(n+m) | `wg[v]`は`pair<int,long long>{to,cost}`。非負辺、有限距離<LLONG_MAX。未到達・表現範囲外はLLONG_MAX。`auto d=dijkstra(wg,0);` |
| 同上 / 0-1 BFS | `zero_one_bfs(g01,s)` → `vector<int>`距離 | O(n+m) / O(n+m) | `g01[v]`は`pair<int,int>{to,0または1}`。未到達-1。`auto d=zero_one_bfs(g01,0);` |
| [scc.cpp](graph/scc.cpp) / 強連結成分 | `scc(g)` → 各頂点の成分ID | O(n+m) / O(n+m) | 反復Kosaraju。IDは0始まり、成分間辺はID昇順。`auto id=scc(g); bool mutual=id[u]==id[v];` |
| [topological_sort.cpp](graph/topological_sort.cpp) / DAG順序 | `topological_sort(g,lexicographical=true)` → 頂点列 | 既定O(m+n log n)、falseならO(n+m) / O(n) | 既定は辞書順最小。閉路なら空配列。空グラフも空配列。`auto order=topological_sort(g,false);` |
| [kruskal.cpp](graph/kruskal.cpp) / 最小全域森 | `kruskal(n,vector<KruskalEdge>)` → `KruskalResult` | O(n+m log(m+1)) / O(n+m) | 辺=`{from,to,cost}`。負辺/自己ループ/多重辺可。`.cost/.edge_ids/.components/.connected()`。`auto r=kruskal(3,{{0,1,2},{1,2,5}});` |
| [lowlink.cpp](graph/lowlink.cpp) / 橋・関節点 | `Lowlink(n,vector<pair<int,int>>)` | 構築O(n+m) / O(n+m) | 無向、非連結/多重辺/自己ループ可。`.bridges`は入力辺ID（DFS帰り順）、`.articulation`は頂点ID昇順。`Lowlink l(3,{{0,1},{1,2}});` |

DFSの `tin/tout` は入る時と出る時の両方で時計を進める。部分木集約には次のEuler Tourを使う。
SCCの相互到達ペア数を求める元の使用例は [examples/scc_pairs.cpp](examples/scc_pairs.cpp) に移した。

## 木

`tree` は `vector<vector<int>>`、根の既定値は0。探索はすべて反復処理。

| ファイル / 用途 | API・入力 → 結果 | 時間 / 空間 | 条件・使用例 |
|---|---|---|---|
| [tree_basics.cpp](tree/tree_basics.cpp) / 根付き木・木DP順序 | `TreeInfo(tree,root=0)` | 構築O(n) / O(n) | `.parent/.depth/.subtree_size/.order`。根の親-1。`TreeInfo t(tree);`、`t.order`の逆順で子から親へDP |
| 同上 / 頂点重み経路和 | `tree_vertex_sums(tree,weights,root=0)` → `vector<long long>` | O(n) / O(n) | **TreeInfoもコピー**。始点を含む。負の重み可、各経路和はlong long内。`auto sums=tree_vertex_sums(tree,weights);` |
| 同上 / 無重み木の直径 | `tree_diameter(tree)` → `TreeDiameter` | O(n) / O(n) | 結果型もコピー。`.from/.to/.length/.path`、lengthは辺数。空木は端点-1・長さ0・空パス。`auto d=tree_diameter(tree);` |
| [lca.cpp](tree/lca.cpp) / 二分ダブリング | `LCA(tree,root=0)` | 構築O(n log n)、問合せO(log n) / O(n log n) | `.query(u,v)`=LCA、`.distance(u,v)`=辺数、`.ancestor(v,k)`=k個上（なければ-1）。k>=0。`LCA l(tree); int a=l.query(u,v);` |
| [euler_tour.cpp](tree/euler_tour.cpp) / 部分木の平坦化 | `EulerTour(tree,root=0)` | 構築O(n)、祖先判定O(1) / O(n) | `.tin/.tout/.order`、部分木`[tin[v],tout[v])`。`e.order[i]`で逆引き。`.is_ancestor(u,v)`。**頂点を一度ずつ並べる方式**で、2n-1の歩行列は生成しない |
| [hld.cpp](tree/hld.cpp) / パス・部分木分解 | `HLD(tree,root=0)` | 構築O(n)、LCA/パスO(log n)、部分木O(1) / O(n) | `.lca(u,v)`、`.path(u,v,edge=false)`、`.subtree(v,edge=false)`。例は後述 |
| [rerooting.cpp](tree/rerooting.cpp) / 全方位木DP | `rerooting(g,identity,merge,add_vertex,lift,root=0)` → 全根のDP配列 | 各操作O(1)ならO(n) / O(n) | `g[v]`=`{to,edge_id}`、同じ無向辺の両側は同じID。mergeは結合則・単位元を持つ。可換性不要。例は後述 |

選択目安: 親と木DP順だけなら `TreeInfo`。LCAとk個上の祖先なら `LCA`。
部分木区間だけなら `EulerTour`。パス集約も必要なら `HLD`。
これらは独立しており、LCAだけの問題にHLDは不要。HLDはLCAも求められるが、k個上の祖先APIは持たない。

```cpp
// EulerTour本体を貼った後: 部分木の頂点数はtout[v]-tin[v]。
EulerTour e(tree);
vector<long long> flat(tree.size());
for(int v=0; v<(int)tree.size(); ++v) flat[e.tin[v]]=weight[v];
// flat上の[e.tin[v],e.tout[v])をACL fenwick_tree/segtreeで集約する。
```

HLDの `.pos[v]` は頂点→配列位置、`.vertex[i]` はその逆。`.path(u,v)` は **u→vの順序**の `Segment{l,r,reverse}` 列。
`reverse=false` はlからr-1、trueはr-1からlへ読む。可換な和/最小値では向きを無視できる。
非可換な合成では、区間データ構造に正順・逆順の両方を持たせる。[ACL segtreeでアフィン変換を合成する実行例](examples/hld_path.cpp) を参照。

辺重みは **親との辺を子のposへ格納**する。`path(u,v,true)` はLCAを除き、`subtree(v,true)` はvの親辺を除く。
同じ頂点同士の辺パスは空。向きにより辺の作用が変わる場合は、上向き用と下向き用の作用も別途用意する。

全方位木DPの操作:

- `merge(a,b)` は隣接側からの寄与を結合する。結合順は各頂点の隣接リスト順。
- `add_vertex(aggregate,v)` はv自身を追加したDP値を返す。
- `lift(dp,from,to,edge_id)` は辺を通してto側へ渡す寄与を返す。辺重みはedge_idから外部配列を参照できる。
- 戻り値 `[v]` はvを根にしたDP。空木は空配列。探索用rootを変えても結果は変わらない。

[距離総和の実行例](examples/rerooting.cpp) では `{距離和,頂点数}` を使う。
文字列など操作自体が長さに比例する型では、全体がO(n)になるとは限らない。

## データ構造

| ファイル / 用途 | API・入力 → 結果 | 時間 / 空間 | 条件・使用例 |
|---|---|---|---|
| [union_find.cpp](data_structure/union_find.cpp) / 連結成分 | `UnionFind(n)`、`.root/.unite/.same/.size` | 構築O(n)、操作ならしO(α(n)) / O(n) | 既存API維持。`UnionFind u(3); u.unite(0,1); bool yes=u.same(0,1);`。通常はACL dsu推奨 |
| [weighted_union_find.cpp](data_structure/weighted_union_find.cpp) / ポテンシャル差制約 | `WeightedUnionFind(n)` | 構築O(n)、操作ならしO(α(n)) / O(n) | `.unite(x,y,w)`はp[y]-p[x]=wを追加、矛盾ならfalse。`.diff(x,y)`は`optional<long long>`、非連結はnullopt。`.same/.size/.root/.weight`あり。`u.unite(0,1,7); auto d=u.diff(0,1);` |
| [fenwick_tree.cpp](data_structure/fenwick_tree.cpp) / 点加算・区間和 | `FenwickTree(n)`、`.add(i,x)`、`.sum(r)`、`.sum(l,r)` | 構築O(n)、操作O(log n) / O(n) | 和・内部部分和がlong long内。`.lower_bound(x)`はprefix>=xとなる最小添字、なければn（x<=0なら0）。下限探索時は全要素非負。`FenwickTree f(3); f.add(0,4); auto x=f.sum(0,2);` |
| [segment_tree.cpp](data_structure/segment_tree.cpp) / 点代入・区間最小 | `SegmentTree(n)` または `SegmentTree(vector<long long>)` | 構築O(n)、更新/問合せO(log n)、get O(1) / O(n) | `.update(i,x)/.query(l,r)/.get(i)`。初期値と空区間はLLONG_MAX。`SegmentTree s(vector<long long>{3,1}); auto x=s.query(0,2);`。汎用用途はACL segtree |
| [sparse_table.cpp](data_structure/sparse_table.cpp) / 静的区間最小 | `SparseTable<T>(values)`、`.query(l,r)` → T | 構築O(n log n)、問合せO(1) / O(n log n) | 更新不可、比較可能なT、queryは非空区間のみ。空配列で構築可。`SparseTable<int> s(vector<int>{3,1,4}); int x=s.query(1,3);` |

重み付きUFは保存される根・親からの差分、およびdiffの返り値がlong longに収まること。
union by sizeと経路圧縮を使う。UFのrootのみ再帰だが、経路圧縮前でも深さはO(log n)に抑えられる。

## 数学

| ファイル / 用途 | API・入力 → 結果 | 時間 / 空間 | 条件・使用例 |
|---|---|---|---|
| [combination.cpp](math/combination.cpp) / 二項係数 | `Combination<Mint>(max_n)`、`.com(n,k)` → Mint | 構築O(max_n+log mod)、問合せO(1) / O(max_n) | 素数mod、0<=max_n<mod。n<0/k<0/k>nなら0。それ以外はn<=max_n。`Combination<atcoder::modint998244353> c(1000); auto x=c.com(10,3);` |
| [eratosthenes.cpp](math/eratosthenes.cpp) / 篩・素因数分解 | `Eratosthenes(N)` | 構築O(N log log N) / O(N) | N>=0。`.is_prime(x)` O(1)、`.factorize(x)` O(log x)→`{素因数,指数}`列、`.divisors(x)`→昇順約数（d個ならO(log x+d log d)）。`.primes/.min_factor`も保持。分解は1<=x<=N。`Eratosthenes e(100); auto f=e.factorize(84);` |
| [mod_pow.cpp](math/mod_pow.cpp) / modular累乗・素数逆元 | `modpow(a,b,mod)`、`modinv(a,mod)` → long long | O(log b)、逆元O(log mod) / O(1) | b>=0,mod>=1。逆元は素数mod>=2かつa%mod!=0。負a可、積は128bit。`auto x=modpow(-2,10,998244353);`。一般のmod演算にはACL modint推奨 |
| [extended_gcd.cpp](math/extended_gcd.cpp) / 拡張GCD | `extGCD(a,b,x,y)` → 非負gcd、x/yへ係数出力 | O(log(max(abs(a),abs(b))+1)) / 同じ深さの再帰 | ax+by=g、a=b=0も可。a,bはLLONG_MIN以外。`long long x,y; auto g=extGCD(12,18,x,y);` |
| 同上 / 一次不定方程式 | `solveDiophantine(a,b,c,x,y,g)` → 解の有無 | 同上 | **extGCDもコピー**。解があればax+by=c、g=gcd。選ばれる特殊解がlong long内。a=b=0はc=0のみ解あり。`long long x,y,g; bool ok=solveDiophantine(3,5,1,x,y,g);` |
| [digits.cpp](math/digits.cpp) / 桁数・整数累乗・回文 | `keta(x,base)`→桁数、`pw(a,b)`→整数累乗、`iskaibun(x,base)`→bool、`make_kaibun(x)`→set | 桁数/判定O(log_base(x+1))、累乗O(log b)、生成O(x log(x+1)) | x>=0,base>=2。0は1桁。pwはb>=0・結果long long内、0^0=1。生成は1..xを左半分とする十進回文で、long long内のみ返す。`bool p=iskaibun(121,10); auto s=make_kaibun(100);` |

Combinationは必要な範囲の階乗・逆階乗だけを保持する。dynamic_modintを使う場合は構築後にmodを変えない。

## 文字列・幾何・DP・その他

| ファイル / 用途 | API・入力 → 結果 | 時間 / 空間 | 条件・使用例 |
|---|---|---|---|
| [manacher.cpp](string/manacher.cpp) / 回文 | `Manacher(string)` | 構築O(n)、判定O(1)、最長探索O(n) / O(n) | `.odd[i]`は文字i中心の半径、`.even[i]`はi-1とiの間の半径。`.is_palindrome(l,r)`、`.longest_palindrome()`→{開始,長さ}（最左優先）、`.radius_at(i)`はダミー入り列上。空文字可。`Manacher m("abba"); bool p=m.is_palindrome(0,4);` |
| [z_algorithm.cpp](string/z_algorithm.cpp) / 接頭辞一致 | ACL `atcoder::z_algorithm(s)` → vector<int> | O(n) / O(n) | 自作再実装なし。z[i]=sとs[i..n)のLCP。非空ならz[0]=n、空なら空。`auto z=atcoder::z_algorithm(string("ababa"));` |
| [angle_sort.cpp](geometry/angle_sort.cpp) / 偏角ソート | `angsort{x,y}`, `cmp`, `cross`, `half`, `eql` | 比較O(1)、ソートO(n log n) / ソートスタックO(log n) | `cmp`はゼロ→正x軸から反時計回り。`eql`は同じ向き。abs(x/y)<=10^18、crossは128bit。**angsort型と補助関数もコピー**。`sort(p.begin(),p.end(),cmp);` |
| [axis_aligned.cpp](geometry/axis_aligned.cpp) / 矩形・直方体 | `Rect{l,r,d,u}`, `Box{x1,x2,y1,y2,z1,z2}`、`intersect/edge_touch/face_touch/point_touch` | 各O(1) / O(1) | 非退化形状、各軸下端<上端。Rectはintersect/edge_touch、Boxは4種類。境界だけの接触はintersect=false。`bool hit=intersect(Rect{0,2,0,2},Rect{1,3,1,3});` |
| 同上 / 共通体積 | `getIntersectionVolume(min1,max1,min2,max2)`、`getIntersectionVolume3(...,min3,max3)` → long long | O(1) / O(1) | 各引数はlong long[3]のxyz。**box_volume_from_widthsもコピー**。座標差・最終体積はlong long内。`long long a[3]={0,0,0},b[3]={2,2,2}; auto v=getIntersectionVolume(a,b,a,b);` |
| [digit_dp.cpp](dp/digit_dp.cpp) / 特定条件の桁DP例 | `count_digit_conditions(S)` → modint998244353 | O(L×2×3×1024×10) / O(2×3×1024) | **汎用桁DPではない**。「使用数字3種類」「桁和が3の倍数」「数字3を含む」のちょうど1つを満たす1..S。先頭0可、空/0は0。`auto x=count_digit_conditions("100");`。実行例はexamples/digit_dp.cpp |
| [coordinate_compression.cpp](techniques/coordinate_compression.cpp) / 座標圧縮 | `CoordinateCompression<T>(a)`、`.get(x)/.compress(a)/.value(i)/.size()` | 構築O(n log n)、get O(log n)、compress O(k log n)、value/size O(1) / O(n) | getの値は元データに存在するもの。`CoordinateCompression<int> c(vector<int>{9,2,9}); int i=c.get(9);` |
| [two_pointers.cpp](techniques/two_pointers.cpp) / 尺取り | `count_subarrays_sum_at_most(a,K)`→long long個数、`min_subarray_length_sum_at_least(a,K)`→最短長（なし-1） | O(n) / O(1) | 非負long long配列、空区間は数えない。Kは任意。中間和は128bit。`auto count=count_subarrays_sum_at_most({1,2,3},3);` |
| 同上 / 種類数制限 | `longest_subarray_at_most_k_distinct(a,K)` → 最長長 | O(n log(n+1)) / O(n) | 符号自由、比較可能な型。K<=0で0。`int len=longest_subarray_at_most_k_distinct(vector<int>{1,2,1},2);` |
| [prefix_sum.cpp](techniques/prefix_sum.cpp) / 累積和 | `PrefixSum(a)`、`.sum(l,r)` → long long | 構築O(n)、問合せO(1) / O(n) | 保存する各prefixと返却値がlong long内。空配列可。`PrefixSum p({2,-1,4}); auto s=p.sum(1,3);` |
| 同上 / 二次元累積和 | `PrefixSum2D(a)`、`.sum(y1,x1,y2,x2)` → long long | 構築O(HW)、問合せO(1) / O(HW) | 長方形。[y1,y2)×[x1,x2)。空vectorは0×0として扱う。保存prefix/返却値はlong long内。`PrefixSum2D p({{1,2},{3,4}}); auto s=p.sum(0,0,2,1);` |
| [imos.cpp](techniques/imos.cpp) / 区間・矩形加算 | `Imos(n)`、`.add(l,r,x)`、`.build()`→vector<long long>。`Imos2D(h,w)`、`.add(y1,x1,y2,x2,x)`、`.build()`→2D配列 | 構築/build O(n)またはO(HW)、add O(1) / 同じ | 差分は128bit、各最終セルはlong long内。空区間・空配列可。buildは何度でも可能、その後の追加も可。`Imos im(5); im.add(1,4,2); auto a=im.build();` |
| [nim.cpp](game/nim.cpp) / Nimの勝敗 | `nim(heaps)`、`Knim(heaps,K)` → 先手必勝bool | O(n) / O(1) | 非負long longの山、K>=1。通常Nimと1手1..K個を除くゲーム。全山0ならfalse。`bool win=Knim({3,5},2);` |

## ACLとの使い分け

[ACL公式索引](https://atcoder.github.io/ac-library/production/document_ja/index.html) を基準にする。
一般の `dsu/fenwick_tree/segtree/lazy_segtree/modint/maxflow/mincostflow/twosat/convolution` はACLを優先する。
既存のUnionFind/FenwickTree/RMQはAPI互換のため残した。FenwickTreeには下限探索がある。
Kruskalの内部ではACL dsu、二項係数・桁DPではACL modintを利用する。
[Z-algorithm](https://atcoder.github.io/ac-library/production/document_ja/string.html) はACLを直接使う。
[SCC](https://atcoder.github.io/ac-library/production/document_ja/scc.html) もACLで代替できるが、本体には長いグラフでも再帰しない版を残した。

## 検証方法

リポジトリルートで実行する。外部Pythonパッケージは不要、`g++` がPATH上に必要。

```sh
python library/tests/run_tests.py --snippets
python library/tests/run_tests.py --debug-stl
python library/tests/run_tests.py --ubsan
```

`--snippets` は各本体に空のmainを足して個別にコンパイル・実行し、全本体を結合した場合もコンパイルする。
テンプレートの実際の利用は別のC++テストで検証する。
`--ubsan` は使用コンパイラがUndefinedBehaviorSanitizerに対応する場合のみ利用可能。
`--debug-stl` はlibstdc++のイテレータ・コンテナ境界チェックを有効にする。
実行ファイルは一時ディレクトリに作成し、終了時に片付ける。
