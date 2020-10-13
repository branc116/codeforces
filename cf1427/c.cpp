#include "bits/stdc++.h"
int main() {
    int n, r; std::cin >> r >> n;
    std::set<std::tuple<int, int, int, int>> DP;
    DP.insert({0, 0, 1, 1});
    int maxi = 0;
    int bad = 0;
    for(int i = 1; i <= n;i++) {
        int sc = 0;
        int t, x, y; std::cin >> t >> x >> y;
        auto pred = [&] (auto tupy) {
            auto [score, oldt, oldx, oldy] = tupy;
            sc = score;
            // std::cout << std::abs(oldx - x) + std::abs(oldy - y) << '<' << t - oldt << ';';
            return std::abs(oldx - x) + std::abs(oldy - y) <= t - oldt;
        };
        auto begin = DP.begin();
        while(begin != DP.end() && !pred(*begin)) { begin++; }
        if (begin == DP.end()) {
            continue;
        }
        maxi = std::max(maxi, std::abs(sc - 1));
        DP.insert({sc - 1,t, x, y});
        // std::cout <<  '\n';
    }
    std::cout << maxi << '\n';
    return 0;
}