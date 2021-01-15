//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
//#pragma GCC optimize("unroll-loops")
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
//#pragma comment(linker, "/STACK:367077216")
#define _CRT_SECURE_NO_WARNINGS
#include <chrono>
#include <set>
#include <map>
#include <deque>
#include <complex>
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
#define sqrl(a) (ll(a)*ll(a))
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
mt19937 rnd(time(0) + 228 + 'k' + 'e' + 'k' + 'e' + 'r' + 'o' + 'f' + 'e' + 'y');
vector<int> genvec(int sz, int minelem, int maxelem)
{
	++maxelem;
	vector<int> ans(sz);
	for (int i = 0; i < sz; ++i)
	{
		ans[i] = minelem + rnd() % (maxelem - minelem);
	}
	return ans;
}
const ld EPS = 1e-14;//(cos,-sin), (sin, cos)
bool checkprime(int x)
{
	for (int i = 2; i * i <= x; ++i) if (x % i == 0) return 0;
	return 1;
}
const ld PI = acos(-1);
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const ll INF = 2e18;
int mod = MOD7;
const int inf = 1e9;
pair<int, int> calc(vector<int>a, vector<int> b)
{
	map<int, int> cnta;
	map<int, int> cntb;
	for (int i : a) cnta[i]++;
	for (int i : b) cntb[i]++;
	pair<int, int> ans = { 0,0 };
	for (auto i : cnta) ans.second += min(i.second, cntb[i.first]);
	for (int i = 0; i < a.size(); ++i)
	{
		ans.first += (a[i] == b[i]);
	}
	return ans;
}
bool stupid(int n, vector<int> b, int x, int y)
{
	int xs = 1;
	for (int j = 0; j < n; ++j) xs *= n + 1;
	for (int xx = 0; xx < xs; ++xx)
	{
		vector<int> ar;
		int txx = xx;
		for (int j = 0; j < n; ++j)
		{
			ar.pbc(xx % (n + 1));
			xx /= n + 1;
		}
		for (int& i : ar)++i;
		xx = txx;
		if (calc(ar, b).first == x && calc(ar, b).second == y) return 1;
	}
	return 0;
}	
signed main()
{
	fastio();
	int t;
	cin >> t;
	while (t--)
	{
		int n, x, y;
		cin >> n >> x >> y;
		int remx = x, remy = y;
		vector<int> b(n);
		vin(b);
	//	cout << (stupid(n, b, x, y) ? "TRULYES" : "NOOO") << endl;
		set<int> ss;
		for (int i : b) ss.insert(i);
		vector<vector<int>> poses(n + 2);
		for (int i = 0; i < n; ++i)
		{
			poses[b[i]].pbc(i);
		}
		vector<int> ans(n);
		set<pair<int, int>> s;
		for (int i : b)
		{
			s.insert({ -(int)poses[i].size() ,i });
		}
		int xx = x;
		while (xx--)
		{
			auto now = *s.begin();
			s.erase(s.begin());
			ans[poses[now.second].back()] = now.second;
			poses[now.second].pob;
			now.first++;
			if(now.first)	
			s.insert(now);
		}
		y -= x;
		int sm = 0;
		for (auto i : s)
		{
			sm -= i.first;
		}
		
		if (!sm)
		{
			cout << "YES" << endl;
			//vout(ans, ' ');
			//cout << endl;
			continue;
		}
		//int xxx = -(s.begin()->first);
		set<pair<int, int>> ts;
		for (auto i : b)
		{
			if(poses[i].size())
			ts.insert({ poses[i].size(), i });
		}
		bool f = 0;
		while (y--)
		{
			if (!s.size() || !ts.size())
			{
				f = 1;
				cout << "NO" << endl;
				break;
			}
			auto now = *s.begin();
			int elem = now.second;
			auto tnow = *ts.rbegin();
			if (tnow.second == elem) tnow = *ts.begin();
			if (tnow.second == elem)
			{
				cout << "NO" << endl;
				f = 1;
				break;
			}
			ts.erase(tnow);
			tnow.first--;
			ans[poses[tnow.second].back()] = elem;
			poses[tnow.second].pob;
			if (tnow.first) ts.insert(tnow);
			s.erase(now);
			now.first++;
			if (now.first) s.insert(now);
		}
		vector<bool> used(n + 2);
		for (int i : b) used[i] = 1;
		int notused = 0;
		for (int i = 1; i <= n + 1; ++i)
		{
			if (!used[i])notused = i;
		}
		if (f) continue;
		for (int& i : ans)
		{
			if (!i) i = notused;
		}
		int tx = 0;
		int ty = 0;
		vector<int> cntb(n + 2);
		vector<int> cntans(n + 2);
		for (int i : ans) cntans[i]++;
		for (int i : b) cntb[i]++;
		for (int i = 0; i < n; ++i) if (ans[i] == b[i]) tx++;
		for (int i = 1; i <= n + 1; ++i)
		{
			ty += min(cntb[i], cntans[i]);
		}
		if (tx != remx || ty != remy)
		{
			cout << "NO" << endl;
			continue;
		}
		cout << "YES" << endl;
		//vout(ans, ' ');
		//cout << endl;
	}
	//sp;
}