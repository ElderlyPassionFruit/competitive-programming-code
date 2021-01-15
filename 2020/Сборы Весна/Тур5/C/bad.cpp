//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")/
//#pragma GCC optimize("unroll-loops")
/*#pragma GCC optimize("section-anchors")
#pragma GCC optimize("profile-values,profile-reorder-functions,tracer")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize("function-sections")
#pragma GCC optimize("data-sections")
#pragma GCC optimize("branch-target-load-optimize")
#pragma GCC optimize("branch-target-load-optimize2")
#pragma GCC optimize("btr-bb-exclusive")*/
//#pragma comment(linker, "/STACK:367077216")
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <set>
#include <map>
#include <deque>
#include <string>
#include <cstdint>
#include <cmath>
#include <queue>
#include <cassert>
#include <random>
#include <bitset>
#include <iomanip>
#include <numeric>
#include <time.h>//////////////
#include <ctime>
#include <string>
#include <cstdio>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
//#define endl '\n'
#define mp make_pair
#define pbc push_back
#define pob pop_back()
#define empb emplace_back
#define queuel queue<long long>
#define sqr(a) ((a) * (a))
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define pin(p) cin >> p.first >> p.second;
#define uniq(a) sort(all(a));(a).resize(unique(all(a)) - a.begin());
#define rev(v) reverse(v.begin(), v.end());
#define sout(s, c) for (auto i : s) cout << i << c;
#define pout(p) cout << p.first << " " << p.second;
#define er(v, l, r) erase(v.begin() + l, v.begin() + r);
#define vin(v) for (ll i = 0; i < v.size(); ++i) cin >> v[i];
#define vout(v, c) for (int i = 0; i < v.size(); ++i) cout << v[i] << c;
#define pushi(v, a) for (int i = 0; i < a.size(); ++i) v.push_back(a[i]);
#define fastio() ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0); srand(time(NULL))
#define dab(v) for(auto i:v)cout<<i<<' ';
#define sp system("pause")
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 0.001;
const ld EPS2 = 1e-6;
const ld PI = acos(-1);
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const int inf = 1e9;
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
#define int ll
bool cmp(pair<int, int> a, pair<int, int> b)
{
    return a.second + a.first < b.first + b.second;
}
signed main()
{
    fastio();
    int k, n;
    cin >> k >> n;
    vector<pair<pair<char, int>, pair<char, int>>> a(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i].first.first >> a[i].first.second >> a[i].second.first >> a[i].second.second;
    }
    auto ta = a;
    ta.clear();
    ll ans = 0;
    for (int i = 0; i < n; ++i)
    {
        if (a[i].first.first == a[i].second.first)
        {
            ans += abs(a[i].first.second - a[i].second.second);
        }
        else
        {
            ++ans;
            ta.pbc(a[i]);
        }
    }
    vector<pair<int, int>> ns;
    for (int i = 0; i < ta.size(); ++i)
    {
        ns.pbc({ min(ta[i].first.second, ta[i].second.second), max(ta[i].first.second, ta[i].second.second) });
    }
    if (!ns.size())
    {
        cout << ans << endl;
        return 0;
    }
    if (ns.size() == 1)
    {
        cout << ns[0].second - ns[0].first + ans << endl;
        return 0;
    }
    multiset<int> fs;
    multiset<int> ss;
    sort(all(ns), cmp);
    vector<int> suf(ns.size());
    int s1 = 0, s2 = 0;
    for (int i = ns.size() - 1; i >= 0; --i)
    {
        fs.insert(ns[i].first);
        fs.insert(ns[i].second);
        s1 += ns[i].first + ns[i].second;
        while (fs.size() > ss.size())
        {
            s1 -= *fs.rbegin();
            s2 += *fs.rbegin();
            ss.insert(*fs.rbegin());
            fs.erase(fs.find(*fs.rbegin()));
        }
        suf[i] = s2 - s1;
    }
    if (k == 1)
    {
        cout << suf[0] + ans << endl;
        //sp;
        return 0;
    }
    fs.clear();
    s1 = 0, s2 = 0;
    ss.clear();
    ll ansos = 1e18;
    ansos = min(ansos, suf[0]);
    for (int i = 0; i < ns.size()-1; ++i)
    {
        fs.insert(ns[i].first);
        fs.insert(ns[i].second);
        s1 += ns[i].first + ns[i].second;
        while (fs.size() > ss.size())
        {
            s1 -= *fs.rbegin();
            s2 += *fs.rbegin();
            ss.insert(*fs.rbegin());
            fs.erase(fs.find(*fs.rbegin()));
        }
        ansos = min(ansos, s2 - s1 + suf[i + 1]);
    }
    cout << ansos + ans << endl;
    return 0;
    //sp;
}