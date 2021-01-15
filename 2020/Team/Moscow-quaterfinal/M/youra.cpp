//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,abm,mmx,avx,avx2,popcnt,tune=native")
//#pragma GCC optimize("fast-math")
//#pragma GCC optimize("Ofast")
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
//#pragma comment(linker, "/STACK:16777216")
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
#define next next228
#define type type1337
#define right right228
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 1e-14;
const ld EPS2 = 1e-12;
const ld PI = acos(-1);
int mod = (int)998244353;
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const ll INF = 1e18;
const int inf = 1e9;
mt19937 rnd(time(0));
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
int n;
int saolve(vector<pair<int, int>> a)
{
  vector<int> cnt(2 * a.size() + 1, inf);
  int now = 0;
  int ans = 0;
  for (int i = 0; i < a.size(); ++i)
  {
    if (a[i].second == 2) now++;
    else now--;
    if (cnt[a.size() + now] != inf)
    {
      int nxt;
      if (i == a.size() - 1) nxt = n - 1;
      else nxt = a[i + 1].first - 1;
      ans = max(ans, nxt - a[cnt[a.size() + now]].first);
    }
    if (!now)
    {
      int nxt;
      if (i == a.size() - 1) nxt = n - 1;
      else nxt = a[i + 1].first - 1;
      ans = max(ans, nxt + 1);
    }
    cnt[now + a.size()] = min(cnt[now + a.size()], i);
  }
  return ans;
}
int solave(vector<int> a)
{
  int ans = 0;
  for (int i = 0; i < a.size(); ++i)
  {
    for (int j = i; j < a.size(); ++j)
    {
      vector<int> cnt(101);
      for (int jj = i; jj <= j; ++jj) cnt[a[jj]] ++;
      int mx = 0;
      int mxc = 0;
      for (int jj = 1; jj <= 100; ++jj)
      {
        if (cnt[jj] > cnt[mx])
        {
          mx = jj; mxc = 0;
        }
        if (cnt[jj] == cnt[mx])
        {
          mxc++;
        }
      }
      if (mxc >= 2) ans = max(ans, j - i + 1);
    }
  }
  return ans;
}
vector<int> gen()
{
  int n = rnd() % 7 +1;
  vector<int> a(n);
  for (int &i : a) i = rnd() % 10 + 1;
  return a;
}
int solve(vector<int> a)
{
  int n = a.size();
  vector<vector<int>> pos(101);
  int ans = 0;
  for (int i = 0; i < n; ++i)
  {
    pos[a[i]].pbc(i);
  }
  int mx = 0;
  int mxc = 0;
  for (int i = 1; i <= 100; ++i)
  {
    if (pos[i].size() > pos[mx].size()) mx = i, mxc = 0;
    if (pos[i].size() == pos[mx].size()) mxc++;
  }
  if (mxc >= 2)
  {
    return n; 
  }
  for (int i = 1; i <= 100; ++i)
  {
    if (i == mx) continue;
    vector<int> now;
    merge(all(pos[i]), all(pos[mx]), back_inserter(now));
    vector<pair<int, int>> rofl(now.size());
    for (int j = 0; j < now.size(); ++j)
    {
      rofl[j].first = now[j];
      if (a[now[j]] == mx) rofl[j].second = 2;
      else rofl[j].second = 1;
    }
    ans = max(ans, saolve(rofl));
  }
  return ans;
}
signed main()
{
  fastio();
  cin >> n;
  vector<int> a(n);
  vin(a);
  cout << solve(a) << endl;
  /*
  sp;
  while (1)
  {
    auto now = gen();
    if (solve(now) != solave(now))
    {
      vout(now, ' ');
      cout << endl;
      cout << solve(now) << endl;
      cout << solave(now) << endl;
      sp;
    }
  }*/
  //sp;
}