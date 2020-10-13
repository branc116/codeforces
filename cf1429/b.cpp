#include "bits/stdc++.h"
#define rep(m, i) for (int i = 0; i < m.size(); i++)
int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> arr;
    std::vector<int> xc(m), yc(n);
    for (int i = 0; i < n; i++)
    {
        std::string s;
        std::cin >> s;
        for (int j = 0; j < s.size(); j++)
        {
            if (s[j] == '*')
            {
                xc[j]++;
                yc[i]++;
            }
        }
        arr.push_back(std::move(s));
    }
    long long sum = 0;
    rep(arr, i)
    {
        auto y = yc[i];
        for (int j = 0; j < arr[i].size(); j++)
        {
            if (arr[i][j] != '*')
                continue;
            auto x = xc[j];
            sum += (x - 1) * (y - 1);
        }
    }
    std::cout << sum << '\n';
    return 0;
}