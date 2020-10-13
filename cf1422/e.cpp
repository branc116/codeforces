#include "bits/stdc++.h"
constexpr int STR_CUR_SIZE = 10;
std::vector<std::string> vs;
void print(std::string_view sw, int n) {
    std::stringstream ss;
    ss << n << ' ';
    if (sw.size() > STR_CUR_SIZE) {
        ss << sw.substr(0, STR_CUR_SIZE - 3 - 2) << "..." << sw.substr(sw.size() - 2, 2) << '\n';
    }else {
        ss << sw << '\n';
    }
    vs.push_back(ss.str());
}

std::tuple<std::string, bool, char> solve(std::string_view sw) {
    if (sw.size() == 1) {
        print(sw, 1);
        return {std::string(sw), true, sw[0]};
    }
    auto [s, can_drop, last] = solve(sw.substr(1, sw.size() -1));
    if (s.size() == 0) {
        std::string to_ret = std::string(sw.substr(0, 1));
        print(to_ret, 1);
        return {to_ret, true, to_ret[0]};
    }
    char lc = last;
    if (sw[0] == s[0]) {
        if (can_drop) {
            if (s.size() == 1) {
                print(sw.substr(0, 0), 0);
                return {std::string(), true, 0};
            }
            if (s[0] > s[1]) {
                auto ret = s.substr(1, s.size() - 1);
                print(ret, ret.size());
                return {ret, false, last};
            }
            if (s[0] == s[1] && s[0] > last) {
                auto ret = s.substr(1, s.size() - 1);
                print(ret, ret.size());
                return {ret, false, last};
            }
        }
    }
    if (s.size() > 1 && s[0] != last) {
        lc = last;
    }else if (s.size() > 0) {
        lc = s[0];
    } else {
        lc = 0;
    }
    auto a = sw[0] + s;
    print(a, a.size());
    return {a, true, lc};
    // print(sw, sw.size());
}

int main() {
    std::string s; std::cin >> s;
    solve(s);
    std::reverse(vs.begin(), vs.end());
    for(const auto& s : vs) {
        std::cout << s;
    }
    return 0;
}