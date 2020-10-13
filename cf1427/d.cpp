#include <bits/stdc++.h>
using namespace std;
int calcDiff(const vector<short> &l, const vector<short> &r)
{
    int diff = 0;
    for (int i = 0; i < min(l.size(), r.size()); i++)
    {
        diff += l[i] != r[i];
    }
    return diff;
}
void print(const vector<short> &l)
{
    for (auto &&a : l)
    {
        cout << a << ' ';
    }
}
template <class T>
int sum(const vector<T> &vec)
{
    int cur = 0;
    for (auto &&a : vec)
    {
        cur += a;
    }
    return cur;
}
vector<short> permute(vector<short> &v, const vector<short> &buckets)
{
    vector<short> ret;
    reverse(v.begin(), v.end());
    int cur = 0;
    for (int i = 0; i < buckets.size(); i++)
    {
        short bup = buckets[buckets.size() - i - 1];
        for (int j = 0; j < bup; j++)
        {
            ret.push_back(v[cur + bup - j - 1]);
        }
        cur += bup;
    }
    reverse(v.begin(), v.end());
    return ret;
}
bool is_sorted(const vector<short> &v)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] != i + 1)
            return false;
    }
    return true;
}
vector<short> getBuckets(const vector<short> &v)
{
    vector<short> temp;
    short bucket = 1;
    for (short i = 1; i < v.size(); i++)
    {

        if ((v[i] - v[i - 1]) == 1)
        {
            bucket++;
        }
        else if (v.size() - i > 1 && v[i + 1] - v[i - 1] == 2)
        {
            bucket++;
            // temp.push_back(bucket);
            // i++;
            // bucket = 1;
        }
        else
        {
            temp.push_back(bucket);
            bucket = 1;
        }
    }
    temp.push_back(bucket);
    int s = sum(temp);
    if (s != v.size())
    {
        temp.push_back(v.size() - s);
        s = sum(temp);
        if (s != v.size())
        {
            cout << s << "!=" << v.size() << '\n';
            temp.push_back(v.size() - s);
            s = sum(temp);
            abort();
        }
    }
    return temp;
}
bool isSame(const vector<short> &l, const vector<short> &r)
{
    if (l.size() != r.size())
        return false;
    for (int i = 0; i < l.size(); i++)
    {
        if (l[i] != r[i])
            return false;
    }
    return true;
}
vector<vector<short>> solve(vector<short> &v, int depth)
{
    if (is_sorted(v))
        return vector<vector<short>>(depth);
    set<short> visited;
    vector<short> buckets;
    int sz = v.size();
    for (int i = 0; i < (sz - 1);)
    {
        short cur = v[i], next = v[i + 1];
        visited.insert(cur);
        int smallest = cur;
        int j = 0;
        int n = 1;
        for(;next - 1 == cur && (i + j + 1) < sz;) {
            j++;
            next = v[i + j + 1];
            cur = v[i + j];
            n++;
            visited.insert(cur);
        }
        buckets.push_back(n);
        if ((smallest - 1) != 0 && visited.find(smallest - 1) == visited.end())
        {
            n = 1;
            // visited.insert(next);
            j++;
            cur = v[i + j];
            while ((i + j) < sz && cur != (smallest - 1))
            {
                visited.insert(cur);
                j++;
                n++;
                cur = v[i + j];
            }
            buckets.push_back(n);
        }
        i += j + 1;
    }
    auto sss = sum(buckets);
    if (sss < v.size()) buckets.push_back(v.size() - sss);
    // for(int i= 0;i<depth;i++) cout << ' ';
    // print(v); cout << "| "; print(buckets); cout << '\n';
    auto next = permute(v, buckets);
    auto sol = solve(next, depth + 1);
    sol[depth] = buckets;
    return sol;
}
int main()
{
    vector<short> s;
    // for(short i = 1;i<=902;i++) {
    //     s.push_back(i);
    // }
    // vector<short> s2 = s;

    // vector<std::tuple<int, vector<short>>> difz;
    // map<int, vector<vector<short>>> maps;
    // size_t m = 0;
    // int max_p = 100;
    // do
    // {
    //     // print(s);
    //     flush(cout);
    //     auto sol = solve(s, 0);
    //     m = max(sol.size(), m);
    //     // cout << ' ' << sol.size() << "\n";
    //     random_shuffle(s.begin(), s.end());
    // } while (max_p-- > 0);
    // cout << m;
    int n; cin >> n;
    for(int i = 0; i < n; i++) {
        short sorty; cin >> sorty;
        s.push_back(sorty);
    }
    auto sol = solve(s, 0);
    cout << sol.size() << '\n';
    for(auto&& a : sol) {
        cout << a.size() << ' ';
        print(a);
        cout << '\n';
    }
    return 0;
}