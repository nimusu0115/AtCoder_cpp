// 元のdigitDPの実行例。問題固有の3条件はdp/digit_dp.cppを参照。
// 提出時はinclude行の代わりに対象.cppを貼り付ける。
#include "../dp/digit_dp.cpp"

int main() {
    string s;
    if(!(cin>>s)) return 0;
    cout<<count_digit_conditions(s).val()<<'\n';
}
