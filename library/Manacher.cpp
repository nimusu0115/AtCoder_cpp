#include<bits/stdc++.h>
using namespace std;

// Manacher法で文字列中の回文を O(N) で前計算する。
// 各文字の間と両端にダミー記号を挟むことで、奇数長・偶数長を同時に扱う。
// 文字と衝突しないよう、変換後の文字列は vector<int> で持ち、ダミー記号を -1 とする。
struct Manacher{
    string S;
    vector<int> transformed;
    vector<int> radius;
    vector<int> odd;
    vector<int> even;

    explicit Manacher(const string& s) : S(s){
        int N = static_cast<int>(S.size());

        // S="abba" なら transformed={-1,'a',-1,'b',-1,'b',-1,'a',-1}。
        transformed.assign(2 * N + 1,-1);
        for(int i = 0;i < N;i++){
            transformed[2 * i + 1] = static_cast<unsigned char>(S[i]);
        }

        int M = static_cast<int>(transformed.size());
        radius.assign(M,0);
        odd.assign(N,0);
        even.assign(N,0);

        // ダミー記号を含む変換後の列に対してManacher法を1回行う。
        // radius[i]は中心i自身を含む回文半径。
        int left = 0;
        int right = -1;
        for(int i = 0;i < M;i++){
            int current_radius = 1;
            if(i <= right) current_radius = min(radius[left + right - i],right - i + 1);

            while(i - current_radius >= 0 && i + current_radius < M
                  && transformed[i - current_radius] == transformed[i + current_radius]){
                current_radius++;
            }
            radius[i] = current_radius;

            if(i + current_radius - 1 > right){
                left = i - current_radius + 1;
                right = i + current_radius - 1;
            }
        }

        // 元文字列上で使いやすいよう、奇数長・偶数長の半径も取り出しておく。
        // 奇数長の回文の長さは 2*odd[i]-1、偶数長は 2*even[i]。
        for(int i = 0;i < N;i++){
            odd[i] = radius_at(2 * i + 1) / 2;
            even[i] = radius_at(2 * i) / 2;
        }
    }

    // 変換後の位置 index を中心とする回文半径を返す。
    int radius_at(int index) const{
        return radius[index];
    }

    // 半開区間 [l,r) が回文なら true を返す。
    // 前提: 0 <= l <= r <= S.size()。
    bool is_palindrome(int l,int r) const{
        int length = r - l;
        if(length <= 1) return true;

        // 元文字列の区間 [l,r) の中心は、変換後では l+r の位置に対応する。
        int center = l + r;
        return radius[center] >= length + 1;
    }

    // 最長回文部分文字列を {開始位置,長さ} で返す。
    // Sが空文字列なら {0,0} を返す。同じ長さなら開始位置が小さいものを選ぶ。
    pair<int,int> longest_palindrome() const{
        int best_start = 0;
        int best_length = 0;

        for(int center = 0;center < static_cast<int>(transformed.size());center++){
            int length = radius[center] - 1;
            int start = (center - length) / 2;
            if(length > best_length || (length == best_length && start < best_start)){
                best_start = start;
                best_length = length;
            }
        }
        return {best_start,best_length};
    }
};
