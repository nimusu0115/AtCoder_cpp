#include <atcoder/string>

// ACLをそのまま使う。O(N)。自作実装は不要。
// z[i] = sとs[i..N)の最長共通接頭辞の長さ。空列なら空、非空ならz[0]=N。
// 例: auto z = atcoder::z_algorithm(std::string("ababa")); // {5,0,3,0,1}
using atcoder::z_algorithm;
