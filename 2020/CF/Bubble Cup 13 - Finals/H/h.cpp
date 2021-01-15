//#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math")
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
//#pragma GCC optimize("inline")
//#pragma comment(linker, "/STACK:167077260")
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
#include <climits>
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
#define lsqr(a) (ld(a) * a)
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
#define left left228
#define calc calc228
#define type type1337
#define right right228
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 1e-7;
const ld EPS2 = 1e-12;
const ld PI = acos(-1);
int mod = (int)998244353;
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const int inf = 1e9;
mt19937 rnd(time(0));
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
map<char, pair<pair<int, int>, pair<int, int>>> rofl;
ld calc(char type, int secs)
{
    auto nw = rofl[type];
    if (nw.first.first > nw.second.first) swap(nw.first, nw.second);
    int kek = nw.second.first - nw.first.first;
    int now = 24 * 3600 - kek;
    if (nw.first.first >= secs)
    {
        return (ld)nw.first.second + (ld)(nw.second.second - nw.first.second) / now * (nw.first.first - secs);
    }
    if (nw.second.first <= secs)
    {
        return (ld)nw.second.second + (ld)(nw.first.second - nw.second.second) / now * (secs - nw.second.first);
    }
    return (ld)nw.first.second + (ld)(nw.second.second - nw.first.second) / kek * (secs - nw.first.first);
}
int cw(string x)
{
    return stoi(x.substr(0, 2)) * 3600 + stoi(x.substr(3, 2)) * 60 + stoi(x.substr(6, 2));
}
ld ans = 0;
int tma = -228;
string fs, ss;
map<char, int> cfs;
map<char, int> css;
void rel(int tm)
{
    ld ans1 = 0, ans2 = 0;
    for (auto i : cfs)
    {
        ans1 += calc(i.first, tm) *i.second;
    }
    for (auto i : css) ans2 += calc(i.first,tm) * i.second;
    if (ans1 - ans2 > ans + EPS)
    {
        ans = ans1 - ans2;
        tma = tm;
    }
}
string backw(int t)
{
    string hh = to_string(t / 3600);
    while (hh.size() < 2) hh = "0" + hh;
    t %= 3600;
    string mm = to_string(t / 60);
    while (mm.size() < 2) mm = "0" + mm;
    t %= 60;
    string ss = to_string(t);
    while (ss.size() < 2) ss = "0" + ss;
    return hh + ":" + mm + ":" + ss;
}
signed main()
{
    fastio();
    for (int i = 0; i < 4; ++i)
    {
        char a;
        cin >> a;
        string fs; int fss;
        string ss;
        int sss;
        cin >> fs >> fss >> ss >> sss;
        rofl[a] = { {cw(fs), fss}, {cw(ss), sss} };
    }
    cin >> fs >> ss;
    for (auto i : fs) cfs[i]++;
    for (auto i : ss) css[i]++;
    for (int i = 0; i < 24 * 3600; ++i) rel(i);
    if (tma == -228)
    {
        cout << "We can't win!";
    }
    else
    {
        cout << backw(tma) << endl << fixed << setprecision(2) << ans;
    }
    //sp;
}