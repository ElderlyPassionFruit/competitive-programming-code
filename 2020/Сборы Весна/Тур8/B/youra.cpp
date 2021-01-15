//#pragma GCC optimize("Ofast,no-stack-protector")
//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2,tune=native")
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
#define sp system("pause")
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
const ld EPS = 1e-5;
const ld EPS2 = 1e-6;
const ld PI = acos(-1);
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const ll inf = 4e9;
const ll INF = 1000 * 1000 * 1000ll * 1000 * 1000 * 1000;
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
#define int ll
struct point
{
	int x, y;
	point(int _x, int _y)
	{
		x = _x, y = _y;
	}
	point()
	{
		x = 0, y = 0;
	}
};
struct line
{
	int a, b, c;
};
point operator-(point a, point b)
{
	return { a.x - b.x, a.y - b.y };
}
point operator+(point a, point b)
{
	return { a.x + b.x, a.y + b.y };
}
int operator*(point a, point b)
{
	return a.x * b.y - a.y * b.x;
}
int operator%(point a, point b)
{
	return a.x * b.x + a.y * b.y;
}
int len(point a)
{
	return a.x * a.x + a.y * a.y;
}
bool cmp(point a, point b)
{
	if (a * b == 0) return len(a) < len(b);
	return a * b > 0;
}
vector<point> ch(vector<point> a)
{
	point mn = { inf,inf };
	for (auto i : a)
	{
		if (i.x < mn.x)mn = i;
		else if (i.x == mn.x && i.y < mn.y) mn = i;
	}
	for (auto& i : a) i = i - mn;
	sort(all(a),cmp);
	vector<point> st;
	for (auto i : a)
	{
		while (st.size() > 2 && (st[st.size() - 2] - st.back()) * (i - st.back()) >= 0)
		{
			st.pob;
		}
		st.pbc(i);
	}
	for (auto& i : st) i = i + mn;
	return st;
}
point perp(point a)
{
	return { -a.y,a.x };
}
ld dist(point x, point a, point b)
{
	return (ld)abs((a - x) * (b - x)) / sqrt(len(a - b));
//	return min(len(a - x), len(b - x));
}
pair<int, int> intersect(pair<int, int> a, pair<int, int> b)
{
	if (a.first > b.first) swap(a, b);
	return { max(a.first, b.first), min(a.second, b.second) };
}
int sgn(int x)
{
	return (x > 0 ? 1 : (x == 0 ? 0 : -1));
}
bool intaer(point a, point b, point c, point d)
{
	pair<int, int> fs = { a.x,b.x };
	pair<int, int> ss = { c.x,d.x };
	if (fs.first > fs.second)swap(fs.first, fs.second);
	if (ss.first > ss.second)swap(ss.first, ss.second);
	pair<int, int> lol = intersect(fs, ss);
	if (lol.first > lol.second) return 0;
	fs = { a.y,b.y };
	ss = { c.y,d.y };
	if (fs.first > fs.second)swap(fs.first, fs.second);
	if (ss.first > ss.second)swap(ss.first, ss.second);
	lol = intersect(fs, ss);
	if (lol.first > lol.second) return 0;
	int fss = (c - a) * (b - a);
	int sss = (d - a) * (b - a);
	if (sgn(fss) * sgn(sss) >= 0) return 0;
	fss = (b - c) * (d - c);
	sss = (a - c) * (d - c);
	if (sgn(fss) * sgn(sss) >= 0) return 0;
	return 1;
}
point operator*(point a, int x)
{
	return { a.x * x, a.y * x };
}
bool inter(point a, point b, vector<point>& x)
{
	for (int i = 0; i < x.size(); ++i)
	{
		if (intaer(a, b, x[i], x[(i + 1) % x.size()]))
		{
			return 1;
		}
	}
	return 0;
}
bool bel(point a, point b, point c)
{
	return (c - a) * (b - a) == 0 && (a - c) * (b - c) == 0 && b.x >= min(c.x,a.x) && b.x <= max(c.x,a.x) && b.y >= min(c.y,a.y) && b.y<=max(c.y, a.y);
}
bool operator==(point a, point b)
{
	return a.x == b.x && a.y == b.y;
}
signed main()
{
	fastio();
	int n;
	cin >> n;
	point x;
	cin >> x.x >> x.y;
	vector<point> a(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> a[i].x >> a[i].y;
	}
	if (n == 1)
	{
		point xx = a[0] - x;
		xx.x = -xx.x;
		xx.y = -xx.y;
		point ans = x + xx;
		cout << "YES" << endl;
		cout << ans.x << ' ' << ans.y << endl;
	//	sp;
		return 0;
	}
	if (n == 2)
	{
		point xx = a[1] - a[0];
		point ans = x + perp(xx);
		if (intaer(a[0], a[1], x, ans)) ans = x - perp(xx);
		cout << "YES" << endl;
		cout << ans.x << ' ' << ans.y;
//		sp;
		return 0;
	}
	auto chh = ch(a);
	ld sum = 0;
	n = chh.size();
	bool ff = 0;
	for (int i = 0; i < n; ++i)
	{
		point fs = chh[i] - x;
		point ss = chh[(i + 1) % n] - x;
		sum += atan2(fs * ss, fs % ss);
		if (bel(chh[i], x, chh[(i + 1) % n])) ff = 1;
	}
	if (abs(sum - 2 * PI) < EPS && ! ff)
	{
		cout << "NO" << endl;
	//	sp;
		return 0;
	}
	ld mnd = 1e18;
	int ti = 0;
	for (int i = 0; i < chh.size(); ++i)
	{
		if (dist(x, chh[i], chh[(i + 1) % n]) -  EPS < mnd)
		{
			mnd = dist(x, chh[i], chh[(i + 1) % n]);
			ti = i;
		}
	}
	cout << "YES" << endl;
	point tx = perp(chh[ti]- chh[(ti + 1) % n]);
	auto kekes = tx;
	int lol = (tx.y == 0 ? inf : (int)(4e9) / abs(tx.y));
	int kek = (tx.x == 0 ? inf : (int)4e9 / abs(tx.x));
	tx = tx * min(lol, kek);
	if (intaer(x, x + tx, chh[ti], chh[ (ti+1)%n]))
	{
		kekes = { -kekes.x, -kekes.y };
		point ans = x + kekes;
		cout << ans.x << ' ' << ans.y;
		//sp;
		return 0;
	}
	point ans = x + kekes;
	cout << ans.x << ' ' << ans.y;
	//sp;
	return 0;
	//	sp;
}