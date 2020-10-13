#pragma GCC optimize(2)

#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>

template <class c>
using v = std::vector<c>;

template <class c, class after_el_call>
void print(const v<c> &arr, const after_el_call &aec)
{
    for (const auto &a : arr)
    {
        std::cout << a;
        aec();
    }
}
template <class c>
void print(const v<c> &arr)
{
    print(arr, []() { std::cout << ' '; });
}
template <class c, class after_el_call, class after_row_call>
void print(const v<v<c>> &arr, after_el_call aec, after_row_call arc)
{
    for (const auto &a : arr)
    {
        print(a, aec);
        arc();
    }
}
template <class c, class after_el_call>
void print(const v<v<c>> &arr, after_el_call aec)
{
    print(arr, aec, []() { std::cout << '\n'; });
}
template <class c>
void print(const v<v<c>> &arr)
{
    print(
        arr, []() { std::cout << ' '; }, []() { std::cout << '\n'; });
}

void input(v<v<int>> &vec, v<v<int>> &diff, int n, int m)
{
    for (size_t i = 0; i < n; i++)
    {
        vec[i] = v<int>(m);
        diff[i] = v<int>(m);
        for (size_t j = 0; j < m; j++)
        {
            int a;
            std::cin >> a;
            vec[i][j] = a;
        }
    }
}

long long difffs(const v<v<int>> &vvi)
{
    int cur_max = 0;
    long long sum = 0;
    for (size_t i = 0; i < (vvi.size() / 2 + vvi.size() % 2); i++)
    {
        // v<int> row;
        const auto &vi = vvi[i];
        const auto &end = vvi[vvi.size() - 1 - i];
        if (i == vvi.size() - 1 - i) {
            for (size_t j = 0; j < (vi.size() / 2 + vi.size() % 2); j++) {
                auto self = vi[j];
                auto py = vi[vi.size() - 1 - j];
                sum += std::abs(self - py);
            }
            continue;
        }
        for (size_t j = 0; j < (vi.size() / 2 + vi.size() % 2); j++)
        {
            auto self = vi[j];
            auto py = vi[vi.size() - 1 - j];
            auto px = end[j];
            auto pxy = end[vi.size() - 1 - j];
            if (j == vi.size() - 1 - j) {
                sum += std::abs(self - px);
            } else {
                v<int> tmp{self, px, py, pxy};
                std::sort(std::begin(tmp), std::end(tmp));
                int mid = (tmp[1] + tmp[2]) / 2;
                // double mid = (self + py + px + pxy) / 4.0;
                sum += (std::abs(self - mid) + std::abs(py - mid) + std::abs(px - mid) + std::abs(pxy - mid));
            }
        }
    }
    return sum;
}

template <class c>
std::pair<size_t, size_t> abs_max(const v<v<c>> &vvi)
{
    c cur_max = 0;
    size_t x_max = 0, y_max = 0;
    for (size_t i = 0; i < vvi.size(); i++)
    {
        const auto &vi = vvi[i];
        for (size_t j = 0; j < vi.size(); j++)
        {
            if (std::abs(vi[j]) > cur_max)
            {
                cur_max = std::abs(vi[j]);
                x_max = i;
                y_max = j;
            }
        }
    }
    return {y_max, x_max};
}
long long solve(int n, int m)
{
    v<v<int>> vvi(n);
    v<v<int>> diff(n);
    input(vvi, diff, n, m);
    return difffs(vvi);
}
int main()
{
    int t;
    std::cin >> t;
    while (t--)
    {
        int n, m;
        std::cin >> n >> m;
        std::cout << solve(n, m) << '\n';
    }
}