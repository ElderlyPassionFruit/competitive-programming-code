
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
int mod = (int)998244353;
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const int inf = 1e9;
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
const int MAXN = 5228;
vector<int> g[MAXN];
int cl[MAXN];
vector<pair<vector<int>, vector<int>>> comps;
void dfs(int v, int c)
{
	cl[v] = c;
	if (c == 1) comps.back().first.pbc(v);
	else comps.back().second.pbc(v);
	for (int i : g[v])
	{
		if (!cl[i]) dfs(i, 3 - c);
		if (cl[i] == c)
		{
			cout << "NO";
			exit(0);
		}
	}
}
int n, m, n1, n2, n3;
signed main()
{
	fastio();
	cin >> n >> m >> n1 >> n2 >> n3;
	for (int i = 0; i < m; ++i)
	{
		int a, b;
		cin >> a >> b;
		g[a].pbc(b);
		g[b].pbc(a);
	}
	for (int i = 1; i <= n; ++i)
	{
		if (!cl[i])
		{
			comps.pbc({ {},{} });
			dfs(i, 1);
		}
	}
	vector<vector<bool>> dp(comps.size() + 1, vector<bool>(2 * n + 228));
	vector<vector<bool>> p(comps.size() + 1, vector<bool>(2 * n + 228));
	dp[0][0] = 1;
	for (int i = 0; i < comps.size(); ++i)
	{
		for (int w = 0; w <= n; ++w)
		{
			if (!dp[i][w]) continue;
			if (!dp[i + 1][w + comps[i].first.size()])
			{
				dp[i + 1][w + comps[i].first.size()] = 1;
				p[i + 1][w + comps[i].first.size()] = 0;
			}
			if (!dp[i + 1][w + comps[i].second.size()])
			{
				dp[i + 1][w + comps[i].second.size()] = 1;
				p[i + 1][w + comps[i].second.size()] = 1;
			}
		}
	}
	if (!dp[comps.size()][n2])
	{
		cout << "NO";
		return 0;
	}
	cout << "YES" << endl;
	int nown = comps.size(); 
	int now2 = n2;
	vector<int> ans(n + 1);
	while (nown > 0)
	{
		bool x = p[nown][now2];
		if (x) swap(comps[nown - 1].first, comps[nown - 1].second);
		for (int i : comps[nown - 1].first) ans[i] = 2, now2--;
		for (int i : comps[nown - 1].second)
		{
			if (n3)
			{
				ans[i] = 3;
				n3--;
			}
			else
			{
				ans[i] = 1;
				n1--;
			}
		}
		nown--;
	}
	if (n1 + now2 + n3) assert(0);
	for (int i = 1; i <= n; ++i)
	{
		cout << ans[i];
	}
	//sp;
}