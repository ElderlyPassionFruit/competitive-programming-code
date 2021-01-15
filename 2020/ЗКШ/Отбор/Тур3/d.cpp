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

const int N = 20010;
int dp[2][N][2];

const int INF = 1e9 + 10;

void rebuild() {
	for (int i = 0; i < N; ++i) 
	{
		for (int j = 0; j < 2; ++j) 
		{
			dp[0][i][j] = dp[1][i][j];
			dp[1][i][j] = INF;	
		}
	}
}

void build() {
	for (int i = 0; i < N; ++i) 
	{
		for (int j = 0; j < 2; ++j) 
		{
			for (int k = 0; k < 2; ++k) 
			{
				dp[j][i][k] = INF;
			}
		}
	}
}

signed main()
{
	fastio();
	string s, t1, t2;
	cin >> s >> t1 >> t2;
	int n = s.size();
	int n1 = t1.size();
	int n2 = t2.size();
	build();
	dp[0][0][0] = 0;
	dp[0][0][1] = 0;
	for (int i = 1; i <= n; ++i) 
	{
		for (int j = max(0, i - n2); j <= min(n1, i); ++j) 
		{
			for (int k = 0; k < 2; ++k) 
			{
				for (int x = 0; x < 2; ++x) 
				{
					if ((k == 0) && j == 0) continue;
					if ((k == 1) && j == i) continue;
					
					char need = s[i - 1];
					char have = ' ';
					
					if (k == 0) have = t1[j - 1];
					else have = t2[i - j - 1];
					if (need != have) continue;
					if (k == 0) 
					{
						if (x == 0)
						{
							dp[1][j][k] = min(dp[1][j][k], dp[0][j - 1][x]);
						}
						else 
						{
							dp[1][j][k] = min(dp[1][j][k], dp[0][j - 1][x] + 1);
						}
					}
					else
					{
						if (x == 0)
						{
							dp[1][j][k] = min(dp[1][j][k], dp[0][j][x] + 1);
						}
						else 
						{
							dp[1][j][k] = min(dp[1][j][k], dp[0][j][x]);
						}
					}
				}
			}
		}
		rebuild();
	}
	int ans = INF;
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < 2; ++j)
			ans = min(ans, dp[0][i][j]);
	cout << ans << endl;
	//sp;
}