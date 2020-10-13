#include "bits/stdc++.h"
#define DBG 0
class gay {
    
    public:
    
    constexpr gay()  noexcept : eat_shit(0) {}
    static gay instance;
    static gay instance2;
    // const gay& operator <<(auto&&...a) const noexcept {
    //     return *this;
    // }
    constexpr gay operator <<(const auto& a) noexcept {
        return *this;
    }
    private:
    int eat_shit;
    // const gay& operator <<(const auto...a) const noexcept {
    //     return *this;
    // }
};
gay gay::instance = gay();


#if DBG
#define dbg std::cout
#else
#define dbg gay::instance = gay()
#endif
template<class T> void print(T& q) {
    T qtmp;
    while(!q.empty()) {
        qtmp.push(q.top());
        auto val = qtmp.top();q.pop();
        std::cout << "(" << val.first << ", " << val.second << ") ";
    }
    while(qtmp.empty()) {
        q.push(qtmp.top());qtmp.pop(); 
    }
    return;
}
template<class T> void print2(T& q) {
    T qtmp;
    while(!q.empty()) {
        qtmp.push(q.top());
        auto val = qtmp.top();q.pop();
        std::cout << val << " ";
    }
    while(qtmp.empty()) {
        q.push(qtmp.top());qtmp.pop(); 
    }
    return;
}
int bup(std::string &s, int k) // gayWLWLWLWLWL
{
    using pii = std::pair<int, int>;
    std::stack<int> sl;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    bool was_first = false;
    long long count = s[0] == 'W' ? 1 : 0;
    for (int i = 1; i < s.size(); i++)
    {
        if (!was_first && s[i] == 'L')
        {
            sl.push(i);
            was_first = true;
        }
        if (s[i] == 'L' && s[i - 1] == 'W')
            sl.push(i);
        if (s[i] == 'W' && s[i - 1] == 'L')
        {
            if (sl.top() == 3)
                pq.push({1e9 + i - sl.top(), sl.top()});
            else
                pq.push({i - sl.top(), sl.top()});
        }
        if (s[i] == 'W')
        {
            if (s[i - 1] == 'W')
                count += 2;
            else
                count++;
        }
    }
    if (pq.size() != sl.size())
    {
        pq.push({1e9 + s.size() - 3 - sl.top(), sl.top()});
    }
    // print2(sl);
    // print(pq); print(pq);
    dbg << s.substr(3, s.size() - 6) << "(" << count << ", " << k << ") ";
    while (k > 0 && !pq.empty())
    {
        auto [size, i] = pq.top();

        int curi = i;
        auto inc = curi != 3;
        dbg << curi << "~";
        if (curi == 3) curi += size - 1e9 - 1;
        dbg << curi << "| ";
        while (k && s[curi] == 'L')
        {
            char cur = s[curi], last = s[curi - 1], next = s[curi + 1];
            s[curi] = 'W';
            if (last == 'W')
                count += 2;
            else
                count += 1;
            if (next == 'W')
                count += 1;
            k--;
            if (inc)
                curi++;
            else 
                curi--;
            dbg << s.substr(3, s.size() - 6) << "(" << count << ", " << k << ", " << curi << ") ";
        }
        pq.pop();
    }
    return count;
}
int main()
{
    int t;
    std::cin >> t;
    int i = 1;
    while (t--)
    {
        std::string s;
        int k;
        std::cin >> k >> k >> s;
        dbg << i << ": ";
        i++;
        if (s.size() == 1 && (s[0] == 'W' || k > 0)) {std::cout << 1 << '\n'; continue;}
        if (s.size() == 1 && (s[0] == 'L' && k == 0)) {std::cout << 0 << '\n'; continue;}
        s = "gay" + s + "gay";
        std::cout <<  bup(s, k) << '\n';
    }
    return 0;
}