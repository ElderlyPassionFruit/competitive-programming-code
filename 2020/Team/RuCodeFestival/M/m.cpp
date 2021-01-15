//#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
#pragma GCC optimize("unroll-loops")
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
const ll INF = 4e18;
const int mod = MOD7;
#define int ll
const int MAXN = 16;
int n;
int a[MAXN];

int now_a[MAXN], now_have[MAXN];
int dp[MAXN][1 << (MAXN)];
int par[MAXN][1 << (MAXN)];

int sum[1 << (MAXN)];

vector<pair<int, int>> solve(int del_mask) 
{
	int sz_a = 0, sz_have = 0;
	for (int i = 0; i < n; i++)
	{
		if ((del_mask >> i) & 1) 
		{
			now_have[sz_have++] = i;
		}
		else
		{
			now_a[sz_a++] = i;
		}
	}
	for (int mask = 0; mask < (1 << sz_have); mask++)
	{
		sum[mask] = 0;
		for (int i = 0; i < sz_have; i++)
		{
			if ((mask >> i) & 1)
			{
				sum[mask] += a[now_have[i]];
			}
		}
	}
	dp[0][0] = 0;
	for (int mask = 1; mask < (1 << sz_have); mask++) dp[0][mask] = -1;

	for (int i = 1; i <= sz_a; i++) 
	{
		for (int mask = 0; mask < (1 << sz_have); mask++)
		{
			dp[i][mask] = -1;
			for (int submask = mask; ; submask = (submask - 1) & mask) 
			{
				if (dp[i - 1][mask ^ submask] == -1) {
					if (submask == 0) 
					{
						break;
					}
					else 
					{
						continue;
					}
				}
				if (dp[i - 1][mask ^ submask] >= a[now_a[i - 1]] + sum[submask])
				{
					if (submask == 0) 
					{
						break;
					}
					else
					{
						continue;
					}
				}
				if (dp[i][mask] != -1 && dp[i][mask] <= a[now_a[i - 1]] + sum[submask]) 
				{
					if (submask == 0)
					{
						break;
					}
					else
					{
						continue;
					}
				}

				dp[i][mask] = a[now_a[i - 1]] + sum[submask];
				par[i][mask] = submask;
				if (submask == 0) break;
			}
		}
	}

	if (dp[sz_a][(1 << sz_have) - 1] == -1) return { {-1, -1} };
	vector<pair<int, int>> ans;
	int mask_now = (1 << sz_have) - 1;
	for (int i = sz_a; i >= 1; i--) 
	{
		int mask = par[i][mask_now];
		for (int bit = 0; bit < sz_have; bit++)
		{
			if ((mask >> bit) & 1) 
			{
				ans.push_back({ now_have[bit], now_a[i - 1] });
			}
		}
		mask_now ^= mask;
	}
	return ans;
}

int get(int x) 
{
	return __builtin_popcount(x);
}

bool used[MAXN];

int get_pos(int x) 
{
	int ans = 0;
	for (int i = 0; i <= x; i++) 
	{
		ans += used[i] == true;
	}
	return ans;
}

void make_ans(vector<pair<int, int>>& ans) 
{
	fill(used, used + n, true);
	vector<pair<int, int>> nans;
	for (auto i : ans) 
	{
		nans.push_back({ get_pos(i.first), get_pos(i.second) });
		used[i.first] = false;
	}
	ans = nans;
}

void solve() 
{
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	vector<pair<int, int>> ans = { {-1, -1} };
	for (int del_mask = 0; del_mask < (1 << n); del_mask++) 
	{
		if (get(del_mask) > max(n - 7, (n + 1) / 2)) continue;
		auto fans = solve(del_mask);
		if ((fans.size() < ans.size() && !(fans.size() == 1 && fans[0].first == -1)) || (ans.size() > 0 && ans[0].first == -1)) {
			ans = fans;
		}
	}
	make_ans(ans);
	cout << ans.size() << "\n";
	for (auto i : ans) 
	{
		cout << i.first << " " << i.second  << "\n";
	}
}

signed main()
{
	fastio();
	int t;
	cin >> t;
	while (t--)
	{
		solve();
	}
}