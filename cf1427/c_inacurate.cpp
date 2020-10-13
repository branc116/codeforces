#include "bits/stdc++.h"
int main() {
    int n, r; std::cin >> r >> n;
    std::vector<std::tuple<int, int, int, int>> DP(n + 1);
    DP[0] = {0, 1, 1, 0};
    int maxi = 0;
    int bad = 0;
    for(int i = 1; i <= n;i++) {
        int prev = i - bad - 1;
        int sc = 0;
        int t, x, y; std::cin >> t >> x >> y;
        auto pred = [&] (auto tupy) {
            auto [oldt, oldx, oldy, score] = tupy;
            sc = score;
            // std::cout << std::abs(oldx - x) + std::abs(oldy - y) << '<' << t - oldt << ';';
            return std::abs(oldx - x) + std::abs(oldy - y) <= t - oldt;
        };
        while(prev >= 0 && !pred(DP[prev])) {
            prev--;
        }
        // std::cout << '\n';
        if (prev == -1) {
            bad++;
            continue;
        }
        maxi = std::max(maxi, sc + 1);
        DP[i - bad] = {t, x, y, sc + 1};
        
    }
    std::cout << maxi << '\n';
    return 0;
}