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
#define int unsigned long long
int n, d;

string gen(int len, string b) {
	string ans = "";
	for (int i = 0; i < len - 1; ++i) 
	{
		ans += b;
		ans += "*";
	}
	ans += b;
	return ans;
}

string get_mul(string s, int cnt) {
	if (cnt == 0) return "";
	string ans = "";
	for (int i = 0; i < cnt - 1; ++i) 
	{
		ans += s;
		ans += "+";
	}
	ans += s;
	return ans;
}

string gen_start(int n, int d) 
{
	string ans = "";
	while (n) {
		int now = 0;
		string add = "";
		while (now * 10 + d <= n)
			now = now * 10 + d, add += '0' + d;
		int x = d;
		string fadd = "";
		fadd += '0' + d;
		while (now * x <= n) {
			fadd += "+";
			fadd += '0' + d;
			x += d;
		}
		x -= d;
		if (x > 1 && now * x <= n) {
			now *= x;
			add += "*";
			add += "(";
			fadd.pop_back();
			fadd.pop_back();
			add += fadd;
			add += ")";
		}
		ans += add;
		ans += "+";
		n -= now;
	}
	ans.pop_back();
	return ans;
}

void solve() 
{
	cin >> n >> d;
	if (n % d) {
		cout << "no solution";
		return;
	} 
	//cout << gen_start(n, d) << endl;
	//cout << gen_start(n, d).size() << endl;
	assert(gen_start(n, d).size() <= 1000);
	cout << gen_start(n, d) << endl;
	return;
	string kek = "";
	string ans = "";
	if (d == 1) 
	{
		kek = "(1+1)";
		if (n % 2) {
			ans = "1+";
			n--;
		}
		d++;
	}
	else 
	{
		kek += '0' + d;	
	}
	int cnt = 1;
	n /= d;
	while (n) 
	{
		string add = get_mul(gen(cnt, kek), n % d);
		if (add.size())
		{
			ans += add;
			ans += "+";
		}
		n /= d;
		cnt++;
	}
	//if (ans.size() > 1000) {
	//	cout << "no solution" << endl;
	//	return;
	//}
	//cout << ans.size() << endl;
	//assert(ans.size() <= 1000);
	ans.pop_back();
	cout << ans << endl;
}

signed main()
{
	fastio();
	//while (true) {
		solve();
	//}
	//cout << ans.size() << endl;
	//sp;
}






