#include<bits/stdc++.h>
using namespace std;

// 英小文字 a-z のTrie。重複と空文字列に対応する。
// passはこのノードを通る文字列数、terminalはここで終わる文字列数。
// 削除時にノードを物理削除しないため、探索時にはpassも確認する。
struct Trie{
    struct Node{
        array<int,26> next;
        int pass = 0;
        int terminal = 0;

        Node(){
            next.fill(-1);
        }
    };

    vector<Node> nodes;

    Trie(){
        nodes.emplace_back();
    }

    // O(|s|)。文字列はa-zのみ。
    void insert(const string& s){
        int v = 0;
        nodes[v].pass++;

        for(char c : s){
            assert('a' <= c && c <= 'z');
            int x = c - 'a';
            if(nodes[v].next[x] == -1){
                int id = (int)nodes.size();
                nodes[v].next[x] = id;
                nodes.emplace_back();
            }
            v = nodes[v].next[x];
            nodes[v].pass++;
        }
        nodes[v].terminal++;
    }

    // 未登録なら何も変更せずfalse。重複は1個だけ削除。O(|s|)。
    bool erase(const string& s){
        if(count(s) == 0) return false;
        int v = 0;
        nodes[v].pass--;

        for(char c : s){
            int x = c - 'a';
            v = nodes[v].next[x];
            nodes[v].pass--;
        }
        nodes[v].terminal--;
        return true;
    }

    // sの経路が有効ならノード番号、なければ-1。空文字列は根0。
    int walk(const string& s) const{
        int v = 0;
        for(char c : s){
            assert('a' <= c && c <= 'z');
            int x = c - 'a';
            int u = nodes[v].next[x];
            if(u == -1 || nodes[u].pass == 0) return -1;
            v = u;
        }
        return v;
    }

    // 有効な枝を1文字進む。存在しなければ-1。
    int next_node(int v,char c) const{
        assert(0 <= v && v < (int)nodes.size());
        assert('a' <= c && c <= 'z');
        int u = nodes[v].next[c - 'a'];
        if(u == -1 || nodes[u].pass == 0) return -1;
        return u;
    }

    int count(const string& s) const{
        int v = walk(s);
        if(v == -1) return 0;
        return nodes[v].terminal;
    }

    bool contains(const string& s) const{
        return count(s) > 0;
    }

    // sを接頭辞に持つ文字列の個数。空文字列なら全体数。
    int prefix_count(const string& s) const{
        int v = walk(s);
        if(v == -1) return 0;
        return nodes[v].pass;
    }

    bool starts_with(const string& s) const{
        return prefix_count(s) > 0;
    }

    // sと登録済みの文字列との最長共通接頭辞長の最大値。
    int lcp(const string& s) const{
        int v = 0;
        int res = 0;
        for(char c : s){
            int u = next_node(v,c);
            if(u == -1) break;
            v = u;
            res++;
        }
        return res;
    }

    int size() const{
        return nodes[0].pass;
    }

    void clear(){
        nodes.clear();
        nodes.emplace_back();
    }
};
