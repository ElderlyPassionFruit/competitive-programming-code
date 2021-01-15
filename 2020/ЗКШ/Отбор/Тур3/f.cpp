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
const ld EPS = 1e-8;
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

#define int ll

int n, m;
vector<vector<int> > g;

void no() 
{
	cout << 0 << endl;
	exit(0);
}

vector<bool> used;

void dfs(int v) 
{
	used[v] = true;
	for (auto i : g[v])
		if (!used[i])
			dfs(i);
}

void check() {
	used.resize(n, false);
	dfs(0);
	for (auto i : used)
		if (!i)
			no();
}

int cnt = 0;
bool flag = false;


set<pair<int, int> > b;
vector<int> tin, up;
int timer = 0;


bool check(int u, int v) 
{
	return !b.count({min(u, v), max(u, v)});
}

void dfs_cycle(int v, int p) 
{
	cnt++;
	used[v] = true;
	for (auto i : g[v]) 
	{
		if (!check(i, v)) continue;
		if (flag) return;
		if (i == p) continue;
		if (used[i]) 
		{
			flag = true;
			return;
		}
		dfs_cycle(i, v);
	}
	if (flag) return;
	cnt--;
}

int get_cycle() {
	used.assign(n, false);
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (auto v : g[i]) {
			cnt += check(i, v);
		}
		if (!cnt) continue;
		dfs_cycle(i, i);
		break;	
	}
	return cnt;
}

void dfs_bridges(int v, int p) 
{
	used[v] = true;
	tin[v] = timer++;
	up[v] = tin[v];
	for (auto i : g[v]) 
	{
		if (i == p) continue;
		if (!used[i]) 
		{
			dfs_bridges(i, v);
			up[v] = min(up[v], up[i]);
			if (tin[v] < up[i]) 
			{
				b.insert({min(v, i), max(v, i)});
			}
		}
		else 
		{
			up[v] = min(up[v], tin[i]);
		}
	}
}

void make() 
{
	used.assign(n, 0);
	tin.resize(n);
	up.resize(n);
	dfs_bridges(0, 0);
}

void dfs_color(int v) 
{
	used[v] = true;
	for (auto i : g[v]) 
	{
		if (used[i]) continue;
		if (!check(i, v)) continue;
		dfs_color(i);
	}
}

int solve_diff() 
{
	used.assign(n, 0);
	int have = 0;
	for (int i = 0; i < n; i++) 
	{
		if (used[i]) continue;
		bool flag = false;
		for (auto v : g[i]) 
		{
			flag |= check(v, i);
		}
		if (!flag) continue;
		dfs_color(i);
		have++;
	}
	if (have == 1) return -1;
	used.assign(n, 0);
	int ans = 1;
	//cout << "have = " << have << endl;
	for (int i = 0; i < n; i++) 
	{
		if (used[i]) continue;
		bool Flag = false;
		for (auto v : g[i]) 
		{
			Flag |= check(v, i);
		}
		if (!Flag) continue;
		cnt = 0;
		flag = false;
		dfs_cycle(i, i);
		ans *= cnt;
		//cout << "cnt = " << cnt << endl;
		//cout << "i = " << i << endl;
		//cout << "used = " << endl;
		//for (auto j : used)
		//	cout << j << " ";
		//cout << endl;
	}
	return ans;
}

int now;

void dfs_count(int v) {
	now++;
	used[v] = true;
	for (auto i : g[v]) 
	{
		if (!check(i, v)) continue;
		if (!used[i])
		{
			dfs_count(i);
		}
	}
}

int fans;

void dfs_cnt(int v, int bad) 
{
	fans++;
	used[v] = true;
	if (v == bad) return;
	for (auto i : g[v]) 
	{
		if (used[i]) continue;
		if (!check(i, v)) continue;
		dfs_cnt(i, bad);
	}
}

int solve_cross() {
	int v = -1;
	set<int> have;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (auto v : g[i])
			cnt += check(i, v);
		if (cnt == 4) {
			assert(v == -1);
			v = i;
		}
		if (cnt == 3) {
			have.insert(i);
		}
	}
	//cout << "v = " << v << endl;
	if (v == -1) {
		assert(have.size() == 2);
		int u = *have.begin();
		have.erase(have.begin());
		int v = *have.begin();
		have.erase(have.begin());
		int ans = 0;
		vector<int> cnt;
		for (auto i : g[v]) {
			if (!check(i, v)) continue;
			fans = 0;
			used.assign(n, 0);
			used[v] = true;
			dfs_cnt(i, u);
			cnt.push_back(fans);
		}
		assert(cnt.size() == 3);
		ans = cnt[0] * cnt[1] + cnt[1] * cnt[2] + cnt[2] * cnt[0];
		return ans;
	}
	else {
		int ans = 1;
		used.assign(n, 0);
		used[v] = true;
		for (auto i : g[v]) 
		{
			if (used[i]) continue;
			if (!check(i, v)) continue;
			now = 0;
			dfs_count(i);
			now++;
			//cout << "i = " << i << " now = " << now << endl;	
			ans *= now;
		}
		return ans;
	}
}

signed main()
{
	fastio();
	cin >> n >> m;
	if (m < n - 1)
		no();
	g.resize(n);
	for (int i = 0; i < m; i++) 
	{
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	check();
	make();
	if (n - 1 == m) {
		cout << 1 << endl;
		return 0;
	}
	if (n == m) 
	{
		cout << get_cycle() << endl;
		return 0;
	}
	if (n + 1 == m) 
	{
		/*cout << "b = " << endl;
		for (auto i : b) {
			cout << i.first << " " << i.second << endl;
		}
		cout << endl;*/
		int fans = solve_diff();
		if (fans != -1) 
		{
			cout << fans << endl;
			return 0;
		}
		//cout << "puhh" << endl;
		cout << solve_cross() << endl;
		return 0;
	}
	assert(false);
	//sp;
}

/*

9 10
1 5
1 6
1 8
2 6
2 9
3 6
3 9
4 9
5 6
5 7


*/