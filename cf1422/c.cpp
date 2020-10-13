#include <string>
#include <iostream>
#include <utility>
#include <vector>
#include <array>

constexpr long long mod = 1e9+7;
constexpr long long fast_power(long long base, long long power, long long mod) noexcept {
    long long result = 1;
    while(power > 0) {
        if(power & 1) 
            result = (result*base) % mod;
        base = (base * base) % mod;
        power = power / 2; 
    }
    return result;
}
constexpr long long n_c_2(long long n, long long mod) noexcept {
    return (n % mod * (n - 1) % mod) % mod / 2;
}


constexpr auto tst = fast_power(10, 19, mod);
constexpr size_t max_n = 1e5+7;
using seq = std::make_index_sequence<max_n>;
template<size_t... i>
auto pows(std::index_sequence<i...> j) noexcept {
    std::array<long long, sizeof...(i)> a{fast_power(10, i, mod)...};
    return a;
}
template<size_t... i>
auto nc2s(std::index_sequence<i...> j) noexcept {
    std::array<long long, sizeof...(i)> a{n_c_2(i, mod)...};
    return a;
}
auto mods = pows(seq());
auto nc2z = nc2s(seq());


long long strange(long long n, long long mod) {
    long long res = 0;
    for(int i = 0; i < n; i++) {
       res = (res + (mods[i] * (i + 1)) % mod) % mod;
    }
    return res;
}
template<size_t n>
auto strangesf() noexcept {
    std::array<long long, n> a;
    long long res = 0;
    for(int i = 0; i < n; i++) {
       res = (res + (mods[i] * (i + 1)) % mod) % mod;
       a[i] = res;
    }
    return a;
}
auto stranges = strangesf<max_n>();
int main() noexcept {
    std::string s;
    std::cin >> s;
    long long rez = 0;
    for (int i = s.size() - 1; i >= 0; --i)
    {
        long long cur = static_cast<long long>(s[i] - '0');
        rez = (rez + stranges[s.size() - i - 2] * cur % mod) % mod;
        rez = (rez + (cur * (mods[s.size() - i - 1] * nc2z[i + 1] % mod) % mod) % mod) % mod;
        
    }
    std::cout << rez << '\n';
}