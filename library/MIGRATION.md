# 整理前の調査と移行記録

基準コミット: `b982a7e`。対象は追跡済み22ソース。無視されている `library/a.exe` は生成物として保持し、ライブラリには含めない。

## Phase 1: 全ファイルの調査

| 旧ファイル | 機能・計算量 | 問題点と改善方針 / 移行先 |
|---|---|---|
| BFS_normal.cpp | BFS O(V+E)、Dijkstra O((V+E)log E) | グローバル状態とmainを除去。負の木の累積和を未訪問値-1で判定すると再訪する。`graph/bfs.cpp`, `graph/shortest_path.cpp`, `tree/tree_basics.cpp` に分離 |
| BFS_grid.cpp | 4近傍BFS O(HW) | H/W/G/seen/distと方向配列がグローバル。引数と距離戻り値へ。`graph/bfs.cpp` に統合 |
| DFS.cpp | DFS・入出時刻・深さ O(V+E) | グローバル状態、深い再帰。反復DFSの結果構造体へ。`graph/dfs.cpp` |
| SCC.cpp | Kosaraju O(V+E) | グローバル逆辺、深い再帰、main混在。反復版と独立した使用例へ。通常はACLも選択可能。`graph/scc.cpp` |
| TopologicalSort.cpp | 辞書順最小のKahn法 | priority_queueなのでO(E+V log V)。既定動作を維持し表記修正、線形時間queue版を追加。`graph/topological_sort.cpp` |
| LCA.cpp | BFS+ダブリング O(N log N), query O(log N) | 既存実装を活用。空木と深さを超えるancestorの不備を修正。`tree/lca.cpp` |
| UnionFind.cpp | 経路圧縮+サイズ併合、ならしO(α(N)) | 十分簡潔。API維持、不要マクロのみ除去。通常はACL dsu推奨。`data_structure/union_find.cpp` |
| FenwickTree.cpp | 構築O(N)、更新/和/下限O(log N) | API維持。不要マクロ除去、境界assert追加。ACL版と下限探索の使い分けを説明。`data_structure/fenwick_tree.cpp` |
| SegmentTree.cpp | 構築O(N)、更新/RMQ O(log N) | API維持。既存の単位元2^60では大きいlong longの最小値が壊れる。LLONG_MAXへ。汎用用途はACL。`data_structure/segment_tree.cpp` |
| com.cpp | 階乗・逆階乗 O(MAX)、nCk O(1) | 固定10000010要素×3配列で約120MB。必要なnだけ持つmodintテンプレートのクラスへ。`math/combination.cpp` |
| Eratosthenes.cpp | 篩 O(N log log N)、分解O(log x) | 十分簡潔。API維持、範囲assert追加。`math/eratosthenes.cpp` |
| extGCD.cpp | 拡張GCD・不定方程式 O(log max(|a|,|b|)) | 不要テンプレート、mainを除去。符号と係数のオーバーフロー条件を明示。`math/extended_gcd.cpp` |
| modpow.cpp | 累乗/素数逆元 O(log b) | __int128による積は活用。不要マクロ除去。`math/mod_pow.cpp` |
| keta.cpp | 桁数・整数累乗・回文生成 | pwが最後にも不要な二乗をしてオーバーフロー。必要な乗算のみ行い範囲確認、回文を桁列で判定。`math/digits.cpp` |
| Manacher.cpp | 回文半径O(N)、判定O(1) | 既存APIと実装をそのまま活用。`string/manacher.cpp` |
| angsort.cpp | 偏角比較O(1)、sort O(N log N) | 既存APIを維持。不要マクロ除去、外積の座標範囲を明示。`geometry/angle_sort.cpp` |
| rect.cpp | 矩形・直方体の交差/接触 O(1) | 不要ACLと競合する定数/補助関数を除去。退化形状の前提を明示。`geometry/axis_aligned.cpp` |
| InsertionVolume.cpp | 2個/3個の直方体共通体積 O(1) | rectと統合、配列APIを維持、main除去。積を128bit化し返却範囲を確認 |
| digitDP.cpp | 特定3条件の桁DP O(L×2×3×1024×10) | 汎用ではなく問題固有例。505桁の固定配列を2層に縮小、独立関数+使用例へ。`dp/digit_dp.cpp` |
| CoordinateCompression.cpp | 構築O(N log N)、検索O(log N) | 既存API維持。`techniques/coordinate_compression.cpp` |
| Shakutori.cpp | 非負列の個数/最短O(N)、種類数O(N log N) | API維持。和の中間値を128bit化。`techniques/two_pointers.cpp` |
| nim.cpp | 通常/上限付きNim O(N) | API維持、main/不要マクロ除去、K+1のオーバーフロー対処。`game/nim.cpp` |

## Phase 2: 設計

- 分野は `graph/tree/data_structure/math/string/geometry/dp/techniques/game`、名前はsnake_case。
- 本体はmainなしのC++17コード片。標準ヘッダと必要なACLヘッダを含め、他の自作ファイルをincludeしない。
- 0-indexed、半開区間、入力は引数、結果は戻り値、前処理はクラス。空入力の扱いと数値範囲をREADMEで明示。
- 木は非空連結無向木（空木も構築可能）。反復探索でスタック消費を抑える。LCAは既存ダブリングを残し、Euler Tour/HLDを独立実装。HLDの区間には向きを付け、非可換演算にも対応。
- 全方位木DPは結合則と単位元を持つmerge、頂点追加、辺通過の3操作を引数で渡す。隣接リスト順に結合し、可換性は要求しない。
- 優先追加: 木の基本情報/直径/Euler Tour/HLD/全方位木DP、0-1 BFS、Kruskal、Lowlink、重み付きUF、Sparse Table、1D/2D累積和/いもす。
- Z-algorithmはACLの実装を使う。SCCは深いグラフ用の反復実装を保持。Union-Find/Fenwick/RMQの既存APIは残すが、新しい汎用セグメント木などは再実装しない。
- Virtual Tree、重心分解、DSU on Tree、Rolling Hash、KMP、凸包は今回の必須範囲に含めず、未実装として記録する。

## 新旧API

| 旧 | 新 | 理由 |
|---|---|---|
| `bfs_seen(s)`, `bfs_dist(s)` + G/dist | `auto d=bfs(g,s)`; `d[v]!=-1`で到達判定 | グローバル初期化不要 |
| グリッド `bfs_dist({h,w})` | `auto d=grid_bfs(grid,{h,w})` | `vector<string>`、壁文字を指定可能 |
| `bfs_dist(s,V)` | `tree_vertex_sums(g,V,s)` | 木の頂点重み和であり最短路ではない。負の和も許可 |
| `dijkstra(s)` + weighted_graph/dist | `auto d=dijkstra(g,s)` | 重み付き探索を分離 |
| `dfs/dfs_order/dfs_depth(s,d)` + グローバル | `auto r=dfs(g,s)`; `r.depth/r.tin/r.tout/r.preorder/r.postorder` | depthは根0。旧dのオフセットは呼び出し側で足す。tin/toutは旧同様2N時計 |
| `scc()` + G/rG | `auto ids=scc(g)` | 逆辺生成と状態を関数内へ。成分番号のトポロジカル順は維持 |
| `cominit(); com(n,k)` | `Combination<atcoder::modint998244353> c(max_n); c.com(n,k)` | nを明示し、modint別の独立インスタンスを作れる |
| `digitDP.cpp` のmain | `count_digit_conditions(S)` + `examples/digit_dp.cpp` | 問題固有の条件と汎用性を区別 |

ほかの既存公開関数・クラス名は維持する。旧ファイルはGit履歴から復元可能。新しいパスはREADMEを参照。手元のコンテスト解答には変更を加えない。
