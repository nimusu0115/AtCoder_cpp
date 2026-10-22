#include<bits/stdc++.h>
using namespace std;

// Heavy-Light Decomposition。連結無向木、構築O(N)、空間O(N)、再帰なし。
// 部分木区間O(1)、LCAとパス分解O(log N)。他の自作ライブラリ不要。
struct HLD{
    struct Segment{
        int l,r;
        bool reverse;
    };
    vector<int> parent;
    vector<int> depth;
    vector<int> size,heavy;
    vector<int> head,pos,vertex;
    explicit HLD(const vector<vector<int>>& tree,int root = 0){
        int N = static_cast<int>(tree.size());
        parent.assign(N,-1);
        depth.assign(N,-1);
        size.assign(N,1);
        heavy.assign(N,-1);
        head.resize(N);
        pos.resize(N);
        vertex.resize(N);
        if(N == 0) return;
        assert(0 <= root && root < N);
        vector<int> order = {root};
        depth[root] = 0;
        for(int i = 0;i < static_cast<int>(order.size());i++){
            int v = order[i];
            for(int to : tree[v]){
                if(depth[to] != -1) continue;
                parent[to] = v;
                depth[to] = depth[v] + 1;
                order.push_back(to);
            }
        }
        assert(static_cast<int>(order.size()) == N);
        for(int i = N - 1;i > 0;i--){
            int v = order[i],p = parent[v];
            size[p] += size[v];
            if(heavy[p] == -1 || size[v] > size[heavy[p]]) heavy[p] = v;
        }
        int timer = 0;
        vector<pair<int,int>> stack = {{root,root}};
        while(!stack.empty()){
            int v = stack.back().first;
            int h = stack.back().second;
            stack.pop_back();
            while(v != -1){
                head[v] = h;
                pos[v] = timer;
                vertex[timer++] = v;
                for(int to : tree[v]){
                    if(parent[to] != v || to == heavy[v]) continue;
                    stack.push_back({to,to});
                }
                v = heavy[v];
            }
        }
    }

    int lca(int u,int v) const{
        while(head[u] != head[v]){
            if(depth[head[u]] < depth[head[v]]) swap(u,v);
            u = parent[head[u]];
        }
        if(depth[u] < depth[v]) return u;
        return v;
    }

    // 辺重みは子のposに格納する。edge=trueで部分木の根への親辺を除外。
    pair<int,int> subtree(int v,bool edge = false) const{
        return {pos[v] + static_cast<int>(edge),pos[v] + size[v]};
    }

    // u->vの順の半開区間列。reverseならr-1からlへ読む。
    // edge=trueではLCAを除き、辺を子頂点の位置で表す。u==vなら空。
    // 非可換演算は正順/逆順の集約を両方用意する（examples/hld_path.cpp）。
    vector<Segment> path(int u,int v,bool edge = false) const{
        vector<Segment> left,right;
        while(head[u] != head[v]){
            if(depth[head[u]] >= depth[head[v]]){
                left.push_back({pos[head[u]],pos[u] + 1,true});
                u = parent[head[u]];
            }
            else{
                right.push_back({pos[head[v]],pos[v] + 1,false});
                v = parent[head[v]];
            }
        }
        if(depth[u] >= depth[v]){
            int l = pos[v] + static_cast<int>(edge);
            if(l < pos[u] + 1) left.push_back({l,pos[u] + 1,true});
        }
        else{
            int l = pos[u] + static_cast<int>(edge);
            if(l < pos[v] + 1) right.push_back({l,pos[v] + 1,false});
        }
        reverse(right.begin(),right.end());
        left.insert(left.end(),right.begin(),right.end());
        return left;
    }
};
