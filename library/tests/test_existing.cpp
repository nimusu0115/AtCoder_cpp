#include "../graph/bfs.cpp"
#include "../graph/dfs.cpp"
#include "../graph/scc.cpp"
#include "../graph/shortest_path.cpp"
#include "../graph/topological_sort.cpp"
#include "../tree/lca.cpp"
#include "../data_structure/union_find.cpp"
#include "../data_structure/fenwick_tree.cpp"
#include "../data_structure/segment_tree.cpp"
#include "../math/combination.cpp"
#include "../math/eratosthenes.cpp"
#include "../math/extended_gcd.cpp"
#include "../math/mod_pow.cpp"
#include "../math/digits.cpp"
#include "../string/manacher.cpp"
#include "../geometry/angle_sort.cpp"
#include "../geometry/axis_aligned.cpp"
#include "../dp/digit_dp.cpp"
#include "../techniques/coordinate_compression.cpp"
#include "../techniques/two_pointers.cpp"
#include "../game/nim.cpp"

mt19937 rng(480);
int random_int(int n) { return static_cast<int>(rng()%n); }

void graph_tests() {
    assert(bfs({},0).empty() && dfs({},0).depth.empty() && scc({}).empty());
    assert(dijkstra({},0).empty() && zero_one_bfs({},0).empty());
    assert(grid_bfs({}, {0,0}).empty());
    assert(grid_bfs({"#"},{0,0})[0][0] == -1);
    assert(grid_bfs({"."},{0,0})[0][0] == 0);
    for(int trial = 0; trial < 350; ++trial) {
        int n = 1+random_int(12);
        vector<vector<int>> g(n), reach(n,vector<int>(n,10000));
        vector<vector<pair<int,long long>>> wg(n);
        for(int v = 0; v < n; ++v) {
            reach[v][v] = 0;
            for(int to = 0; to < n; ++to) if(random_int(4) == 0) {
                g[v].push_back(to); wg[v].push_back({to,1}); reach[v][to] = min(reach[v][to],1);
            }
        }
        for(int k = 0; k < n; ++k) for(int i = 0; i < n; ++i) for(int j = 0; j < n; ++j)
            reach[i][j] = min(reach[i][j],reach[i][k]+reach[k][j]);
        auto ids = scc(g);
        assert(ids == scc(g));
        for(int v = 0; v < n; ++v) {
            auto d = bfs(g,v); auto dw = dijkstra(wg,v); auto r = dfs(g,v);
            assert(d == bfs(g,v));
            for(int to = 0; to < n; ++to) {
                assert(d[to] == (reach[v][to] < 10000 ? reach[v][to] : -1));
                assert(dw[to] == (d[to] < 0 ? LLONG_MAX : d[to]));
                assert((r.depth[to] >= 0) == (d[to] >= 0));
                assert((ids[v] == ids[to]) == (reach[v][to] < 10000 && reach[to][v] < 10000));
            }
            for(int to : g[v]) assert(ids[v] <= ids[to]);
        }
        for(bool lex : {false,true}) {
            auto order = topological_sort(g,lex);
            bool cyclic = false;
            for(int v = 0; v < n; ++v) for(int to : g[v]) if(reach[to][v] < 10000) cyclic = true;
            assert(order.empty() == cyclic);
            if(!cyclic) {
                vector<int> pos(n);
                for(int i = 0; i < n; ++i) pos[order[i]] = i;
                for(int v = 0; v < n; ++v) for(int to : g[v]) assert(pos[v] < pos[to]);
                if(lex) {
                    vector<int> deg(n);
                    for(auto& row : g) for(int to : row) ++deg[to];
                    for(int v : order) {
                        int smallest = 0;
                        while(deg[smallest] != 0) ++smallest;
                        assert(smallest == v); deg[v] = -1;
                        for(int to : g[v]) --deg[to];
                    }
                }
            }
        }
    }
    vector<vector<pair<int,long long>>> huge(4);
    huge[0] = {{1,LLONG_MAX-2},{2,4}}; huge[1] = {{3,20}}; huge[2] = {{3,6}};
    assert((dijkstra(huge,0) == vector<long long>{0,LLONG_MAX-2,4,10}));
    // グリッドを愚直な隣接リストへ変換して比較。
    for(int trial = 0; trial < 100; ++trial) {
        int h = 1+random_int(8), w = 1+random_int(8);
        vector<string> a(h,string(w,'.'));
        for(auto& row : a) for(char& c : row) if(random_int(3) == 0) c = '#';
        int s = random_int(h*w); a[s/w][s%w] = '.';
        vector<vector<int>> g(h*w);
        for(int y = 0; y < h; ++y) for(int x = 0; x < w; ++x) if(a[y][x] != '#') {
            for(auto [dy,dx] : vector<pair<int,int>>{{0,1},{0,-1},{1,0},{-1,0}}) {
                int ny=y+dy,nx=x+dx;
                if(ny>=0 && ny<h && nx>=0 && nx<w && a[ny][nx]!='#') g[y*w+x].push_back(ny*w+nx);
            }
        }
        auto expected = bfs(g,s); auto actual = grid_bfs(a,{s/w,s%w});
        for(int i = 0; i < h*w; ++i) assert(expected[i] == actual[i/w][i%w]);
    }
}

void structure_tests() {
    FenwickTree empty(0); SegmentTree es(0); UnionFind eu(0);
    assert(empty.sum(0,0) == 0 && empty.lower_bound(1) == 0 && es.query(0,0) == LLONG_MAX);
    SegmentTree big(vector<ll>{LLONG_MAX-1,LLONG_MAX});
    assert(big.query(0,2) == LLONG_MAX-1);
    for(int trial = 0; trial < 100; ++trial) {
        int n = 1+random_int(30); vector<ll> a(n); vector<int> ids(n); iota(ids.begin(),ids.end(),0);
        FenwickTree ft(n); SegmentTree st(a); UnionFind uf(n);
        for(int step = 0; step < 150; ++step) {
            int v = random_int(n), w = random_int(n); ll value = random_int(100);
            ft.add(v,value-a[v]); a[v] = value; st.update(v,value);
            int l = random_int(n+1), r = random_int(n+1); if(l>r) swap(l,r);
            assert(ft.sum(l,r) == accumulate(a.begin()+l,a.begin()+r,0LL));
            assert(st.query(l,r) == (l==r ? LLONG_MAX : *min_element(a.begin()+l,a.begin()+r)));
            assert(st.get(v) == a[v]);
            ll target = random_int(2000), sum = 0; int expected = 0;
            while(expected<n && sum+a[expected]<target) sum += a[expected++];
            assert(ft.lower_bound(target) == expected);
            int old = ids[w], now = ids[v];
            uf.unite(v,w); for(int& id : ids) if(id == old) id = now;
            for(int i = 0; i < n; ++i) {
                assert(uf.same(v,i) == (ids[v] == ids[i]));
                assert(uf.size(i) == count(ids.begin(),ids.end(),ids[i]));
            }
        }
    }
}

void math_tests() {
    using Mint = atcoder::modint998244353;
    Combination<Mint> comb(200), zero(0);
    assert(zero.com(0,0) == Mint(1) && comb.com(-1,0) == Mint(0) && comb.com(2,-1) == Mint(0));
    vector<Mint> row(201); row[0] = 1;
    for(int n = 0; n <= 200; ++n) {
        for(int k = 0; k <= n+1; ++k) assert(comb.com(n,k) == (k<=n ? row[k] : Mint(0)));
        for(int k = min(n+1,200); k>0; --k) row[k] += row[k-1];
    }
    Eratosthenes sieve(3000); assert(Eratosthenes(0).primes.empty());
    for(int n = 1; n <= 3000; ++n) {
        vector<int> div;
        for(int d = 1; d <= n; ++d) if(n%d == 0) div.push_back(d);
        assert(sieve.divisors(n) == div && sieve.is_prime(n) == (div.size() == 2));
        int product = 1; for(auto [p,e] : sieve.factorize(n)) while(e--) product *= p;
        assert(product == n);
    }
    for(ll a = -30; a <= 30; ++a) for(ll b = -30; b <= 30; ++b) {
        ll x,y,g; ll actual = extGCD(a,b,x,y);
        assert(actual == gcd(a,b) && a*x+b*y == actual);
        bool ok = solveDiophantine(a,b,17,x,y,g);
        assert(ok == (g != 0 && 17%g == 0)); if(ok) assert(a*x+b*y == 17);
    }
    ll x,y,g; assert(solveDiophantine(0,0,0,x,y,g));
    for(ll m = 1; m <= 50; ++m) for(ll a = -20; a <= 20; ++a) {
        ll expected = 1%m;
        for(int e = 0; e <= 50; ++e) {
            assert(modpow(a,e,m) == expected);
            expected = (expected*((a%m+m)%m))%m;
        }
    }
    assert(modpow(LLONG_MAX-1,2,LLONG_MAX) == 1 && modinv(3,7) == 5);
    assert(pw(10,18) == 1000000000000000000LL && pw(LLONG_MIN,1) == LLONG_MIN);
    for(int base = 2; base <= 16; ++base) for(int n = 0; n < 1000; ++n) {
        vector<int> d; int x=n; do { d.push_back(x%base); x/=base; } while(x);
        assert(keta(n,base) == static_cast<int>(d.size()));
        assert(iskaibun(n,base) == equal(d.begin(),d.end(),d.rbegin()));
    }
    assert((make_kaibun(2) == set<ll>{1,2,11,22}));
    for(ll n : make_kaibun(1000)) assert(iskaibun(n,10));
}

void other_tests() {
    assert(!nim({}) && nim({1,2}) && !Knim({LLONG_MAX,LLONG_MAX},LLONG_MAX));
    assert(Knim({LLONG_MAX},LLONG_MAX));
    for(int trial = 0; trial < 200; ++trial) {
        int n = random_int(30); vector<ll> a(n);
        for(ll& x : a) x = random_int(8);
        ll k = random_int(20)-2, count_ok=0; int shortest=n+1,longest=0;
        for(int l=0; l<n; ++l) {
            ll sum=0; set<ll> seen;
            for(int r=l; r<n; ++r) {
                sum+=a[r]; seen.insert(a[r]);
                if(sum<=k) ++count_ok;
                if(sum>=k) shortest=min(shortest,r-l+1);
                if(static_cast<int>(seen.size())<=k) longest=max(longest,r-l+1);
            }
        }
        assert(count_subarrays_sum_at_most(a,k)==count_ok);
        assert(min_subarray_length_sum_at_least(a,k)==(shortest==n+1 ? -1 : shortest));
        assert(longest_subarray_at_most_k_distinct(a,static_cast<int>(k))==longest);
        CoordinateCompression<ll> c(a); auto b=c.compress(a);
        for(int i=0; i<n; ++i) assert(c.value(b[i])==a[i]);
        string s; for(int i=0; i<n; ++i) s += static_cast<char>(random_int(256));
        Manacher m(s); int best=0,start=0;
        for(int l=0; l<=n; ++l) for(int r=l; r<=n; ++r) {
            string part=s.substr(l,r-l), rev=part; reverse(rev.begin(),rev.end());
            assert(m.is_palindrome(l,r)==(part==rev));
            if(part==rev && r-l>best) { best=r-l; start=l; }
        }
        assert(m.longest_palindrome()==make_pair(start,best));
        for(int i=0; i<n; ++i) {
            int odd=0,even=0;
            while(i-odd>=0 && i+odd<n && s[i-odd]==s[i+odd]) ++odd;
            while(i-even-1>=0 && i+even<n && s[i-even-1]==s[i+even]) ++even;
            assert(m.odd[i]==odd && m.even[i]==even);
        }
    }
    assert(count_subarrays_sum_at_most({LLONG_MAX,LLONG_MAX},LLONG_MAX)==2);
    assert(min_subarray_length_sum_at_least({LLONG_MAX-1,LLONG_MAX-1},LLONG_MAX)==2);
    unsigned expected=0;
    assert(count_digit_conditions("").val()==0);
    for(int n=0; n<=400; ++n) {
        if(n) {
            string s=to_string(n); set<char> d(s.begin(),s.end()); int sum=0;
            for(char c : s) sum+=c-'0';
            int conditions=(d.size()==3)+(sum%3==0)+(d.count('3')!=0);
            expected += conditions==1;
        }
        if(n<20 || n%13==0) {
            assert(count_digit_conditions(to_string(n)).val()==expected);
            assert(count_digit_conditions("000"+to_string(n)).val()==expected);
        }
    }
    vector<angsort> points={{0,0},{1,0},{2,1},{0,1},{-1,0},{0,-1}};
    for(auto a : points) for(auto b : points) for(auto c : points) {
        assert(!cmp(a,a)); assert(!(cmp(a,b)&&cmp(b,a)));
        if(cmp(a,b)&&cmp(b,c)) assert(cmp(a,c));
    }
    assert(eql({1,2},{2,4}) && !eql({1,0},{-1,0}));
    assert(cross({1000000000000000000LL,0},{0,1000000000000000000LL})>0);
    Rect a{0,2,0,2}; assert(intersect(a,{1,3,1,3}));
    assert(edge_touch(a,{2,3,0,2}) && !edge_touch(a,{2,3,2,3}));
    Box b{0,2,0,2,0,2};
    assert(intersect(b,{1,3,1,3,1,3})); assert(face_touch(b,{2,3,0,2,0,2}));
    assert(edge_touch(b,{2,3,2,3,0,2}) && point_touch(b,{2,3,2,3,2,3}));
    assert(!intersect(b,{3,4,3,4,3,4}));
    ll low[]={0,0,0},high[]={2,2,2},low2[]={1,1,1},high2[]={3,3,3};
    assert(getIntersectionVolume(low,high,low2,high2)==1);
    assert(getIntersectionVolume3(low,high,low2,high2,low,high)==1);
    assert(box_volume_from_widths(LLONG_MAX,LLONG_MAX,0)==0);
    assert(LCA({}).depth.empty());
    LCA single(vector<vector<int>>(1)); assert(single.query(0,0)==0 && single.ancestor(0,INT_MAX)==-1);
}

int main() {
    graph_tests(); structure_tests(); math_tests(); other_tests();
    cout << "existing: randomized graph/data structure/math/string/geometry/DP checks passed\n";
}
