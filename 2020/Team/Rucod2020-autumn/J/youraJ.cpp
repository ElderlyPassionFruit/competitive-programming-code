//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("unroll-loops")
//#pragma GCC optimize("Ofast")
//#pragma GCC optimize("fast-math")
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
#define type type1337
#define right right228
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 1e-6;
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
int n, m, k;
const int MAXN = 1000 + 1;
vector<int> g[MAXN];
int dp[MAXN][2][2];
vector<int> bfs(int v)
{
    vector<int> d(n + 1, inf);
    d[v] = 0;
    queue<int> q;
    q.push(v);
    while (q.size())
    {
        int u = q.front();
        q.pop();
        for (int i : g[u])
        {
            if (d[i] > d[u] + 1)
            {
                d[i] = d[u] + 1;
                q.push(i);
            }
        }
    }
    return d;
}
int solve(int v, int fs, int ss)
{
    if (dp[v][fs][ss] == -1)
    {
        dp[v][fs][ss] = 0;
        for (int i : g[v])
        {
            solve(i, ss, fs);
            if (!dp[i][ss][fs]) dp[v][fs][ss] = 1;
        }
        if (fs)
        {
            auto nw = bfs(v);
            for (int i = 1; i <= n; ++i)
            {
                if ( i!=v && nw[i] <= k)
                {
                    solve(i, ss, 0);
                    if (!dp[i][ss][0]) dp[v][fs][ss] = 1;
                }
            }
        }
    }
    return dp[v][fs][ss];
}
signed main()
{
    fastio();
    for (int i = 0; i < MAXN; ++i) for (int j = 0; j < 2; ++j)for (int k = 0; k < 2; ++k) dp[i][j][k] = -1;
    cin >> n >> m >> k;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        g[a].pbc(b);
    }
    int x = solve(1, 1, 1);
    if (x)cout << "Dasha\n";
    else cout << "Denis\n";
    //sp;
}