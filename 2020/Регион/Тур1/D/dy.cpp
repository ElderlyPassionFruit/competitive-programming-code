//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
/*#pragma GCC optimize("fast-math")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("section-anchors")
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
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <set>
#include <map>
#include <deque>
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
#define sp system("pause")
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 1.5e-4;
const int inf = 1e9;
const ld PI = acos(-1);
int mod = (int)998244353;
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const ll kekmod = 1791791791;
const int MOD2 = MOD9;
const ll bestmod = 1148822869;
const ll secmod = (int) 1e9 + 113;
vector<ll> mods = { kekmod,bestmod };
vector<ll> hashpows = { 37,43,47,53,179,229 };
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count() + 228 + 'i' + 'q' + 1337 + 1488);
ll MOD = mods[rnd() % mods.size()];
ll hashpow = hashpows[rand() % hashpows.size()];
//#define int ll
int n, q;
const int MAXN = 5e5 + 1;
int a[MAXN];
const int MAXQ = 2e6 + 1;
int f[MAXQ];
void add(int i, int x)
{
	for (; i < MAXQ; i |= (i + 1))f[i] += x;
}
int get(int r)
{
	int ans = 0;
	for (; r >= 0; r = (r&(r + 1)) - 1)
	{
		ans += f[r];
	}
	return ans;
}
bool used[MAXQ];
int val[MAXQ];
vector<int> grd[MAXQ];
void upd(int x)
{
	if (!used[x]) return;
	used[x] = 0;
	used[x + 1] = 1;
	val[x] = val[x - 1];
}
bool cmp(pair<pair<int, int>, pair<int,int>> a, pair<pair<int, int>, pair<int,int>> b)
{
	return a.second.first < b.second.first;
}
signed main()
{
	fastio();
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
	}
	vector<pair<pair<int, int>, pair<int,int>>> queries;
	vector<int> ans(q, -1);
	set<pair<int, int>> now;
	for (int i = 1; i <= n; ++i)
	{
		grd[a[i]].pbc(i);
	}
	for (int i = 1; i < MAXQ; ++i)
	{
		val[i] = val[i - 1];
		if (grd[i].size())
		{
			used[i] = 1;
			val[i] = i;
		}
	}
	for (int i = 0; i < q; ++i)
	{
		int t;
		cin >> t;
		if (t == 1)
		{
			int x;
			cin >> x;
			upd(x);
		}
		else
		{
			int l, r, x;
			cin >> l >> r >> x;
			queries.pbc({ {l,r}, {val[x], i} });
		}
	}	
	sort(all(queries), cmp);
	int last = 0;
	for (int i = 0; i < queries.size(); ++i)
	{
		if (queries[i].second.first != last)
		{
			last = queries[i].second.first;
			for (int j : grd[last])
			{
				add(j, 1);
			}
		}
		ans[queries[i].second.second] = get(queries[i].first.second) - get(queries[i].first.first - 1);
	}

	for (int i = 0; i < q; ++i)
	{
		if(ans[i] !=-1)
		cout << ans[i] << endl;
	}
	//sp;
}