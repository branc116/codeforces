#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <tuple>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

int distance_j_tp(const tuple<int, int, int>& j, const pair<int, int>& tp) {
    return min(abs(tp.first - get<1>(j)), abs(tp.second - get<2>(j)));
}
int distance_j_tp(const tuple<int, int, int>& j, const tuple<int, int, int>& tp) {
    return min(abs(get<0>(tp) - get<0>(j)), abs(get<1>(tp) - get<1>(j)));
}
int distance_j_tp(const pair<int, int>& j, const pair<int, int>& tp) {
    return min(abs(tp.first - j.first), abs(tp.second - j.second));
}
int distance_j_end(const pair<int, int>& j, const pair<int, int>& end) {
    return abs(get<0>(end) - get<0>(j)) + abs(get<1>(end) - get<1>(j));
}
template<class a> void print(const a& cont) {
    for(const auto&  el: cont) {
        std::cout << '(' << el.first << ", " << el.second << "), ";
    }
}
int main()
{
    int n, m;
    cin >> n >> m;
    pair<int, int> goal;
    pair<int, int> jura;
    std::vector<std::pair<int, int>> tps(m);
    std::set<tuple<int, int, int>> pairs_xyi;
    std::set<tuple<int, int, int>> pairs_yxi;
    std::vector<std::vector<std::pair<int, int>>> edges(m + 3);
    std::cin >> jura.first >> jura.second >> goal.first >> goal.second;
    if (m == 0) {
        std::cout << distance_j_end(goal, jura);
        return 0;
    }
    edges[m].push_back(std::make_pair(m + 1, distance_j_end(jura, goal)));
    for (int i = 0; i < m; i++)
    {
        int x, y;
        cin >> x >> y;
        pairs_xyi.insert(std::make_tuple(x,y,i));
        pairs_yxi.insert(std::make_tuple(y,x,i));
        tps[i] = std::make_pair(x, y);
        edges[m].push_back(std::make_pair(i, distance_j_tp(jura, tps[i])));
        edges[i].push_back(std::make_pair(m + 1, distance_j_end(tps[i], goal)));
    }
    auto lim =pairs_xyi.end();
    lim--;
    for(auto a = pairs_xyi.begin(); a != lim; a++) {
        auto next = a;next++;
        int a_i = get<2>(*a), next_i = get<2>(*next);
        int dist = distance_j_tp(*a, *next);
        edges[a_i].push_back(std::make_pair(next_i, dist));
        edges[next_i].push_back(std::make_pair(a_i, dist));
    }
    lim = pairs_yxi.end(); lim--;
    for(auto a = pairs_yxi.begin(); a != lim; a++) {
        auto next = a;next++;
        int a_i = get<2>(*a), next_i = get<2>(*next);
        int dist = distance_j_tp(*a, *next);
        edges[a_i].push_back(std::make_pair(next_i, dist));
        edges[next_i].push_back(std::make_pair(a_i, dist));
    }
    std::set<int> been;
    using bup = std::pair<int, int>;
    std::priority_queue<bup, std::vector<bup>, std::greater<bup>> q;
    q.push({0, m});
    int best = distance_j_end(jura, goal);
    while(!q.empty()) {
        auto [cur, i] = q.top(); q.pop();
        if (i == m + 1 && cur < best)
            best = cur;
        if (been.find(i) != been.end())
            continue;
        been.insert(i);
        for(const auto& nb : edges[i]) {
            q.push(std::make_pair(cur + nb.second, nb.first));
        }
    }
    std::cout << best;
    return 0;
}