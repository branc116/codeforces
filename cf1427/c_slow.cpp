#include "bits/stdc++.h"
int DP[512][512];
int DP_o[512][512];
template <class... i>
constexpr inline int mymax(i... ints)
{
    int cur = -1e9;
    auto ml = [&](auto j) { cur = std::max(cur, j); return; };
    (ml(ints), ...);
    return cur;
}
void print(int r) {
    for (int x = 1; x <= r; x++)
    {
        for (int y = 1; y <= r; y++)
        {
            if (DP_o[x][y] < -1)
                std::cout << 'c';
            else 
                std::cout << DP_o[x][y];
            std::cout << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}
int main()
{
    int r, n;
    std::cin >> r >> n;
    for (int i = 0; i <= r + 1; i++)
    {
        for (int j = 0; j <= r + 1; j++)
        {
            DP[i][j] = -1e9;
        }
    }
    DP[1][1] = 0;
    int tr = -1, xr, yr;
    int maxi = 0;
    memcpy(DP_o, DP , sizeof(DP_o));
    for (int t = 1; n; t++)
    {
        if (tr < t)
        {
            std::cin >> tr >> xr >> yr;
            n--;
        }
        for (int x = 1; x <= r; x++)
        {
            for (int y = 1; y <= r; y++)
            {
                DP_o[x][y] = mymax(
                    DP[x - 1][y],
                    DP[x][y - 1],
                    DP[x + 1][y],
                    DP[x][y + 1],
                    DP[x][y]);
            }
        }
        if (tr == t)
        {
            DP_o[xr][yr]++;
        }
        memcpy(DP, DP_o, sizeof(DP_o));
    }
    for (int x = 1; x < r; x++)
    {
        for (int y = 1; y < r; y++)
        {
            maxi = mymax(DP[x][y], maxi);
        }
    }
    std::cout << maxi << '\n';
}