#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,avx2,popcnt,tune=native")
//#pragma GCC optimize("SEX_ON_THE_BEACH")	
 
#define _CRT_SECURE_NO_WARNINGS
 
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
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define matrix vector<vector<ll>>
#define pin(p) cin >> p.first >> p.second;
#define rev(v) reverse(v.begin(), v.end());
#define mx(v) max_element(v.begin(), v.end());
#define mn(v) min_element(v.begin(), v.end());
#define sout(s, c) for (auto i : s) cout << i << c;
#define pout(p) cout << p.first << " " << p.second;
#define er(v, l, r) erase(v.begin() + l, v.begin() + r);
#define vin(v) for (ll i = 0; i < v.size(); ++i) cin >> v[i];
#define vout(v, c) for (int i = 0; i < v.size(); ++i) cout << v[i] << c;
#define pushi(v, a) for (int i = 0; i < a.size(); ++i) v.push_back(a[i]);
#define sin(s, n) for (int i = 0; i < n; ++i){int a; cin >> a; s.insert(a); }
#define fastio() ios_base::sync_with_stdio(0); cout.tie(0); cin.tie(0); srand(time(NULL))
#define sp system("pause")
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
using namespace std;//СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚СЂСџВ¦Р‚
					//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
//++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++--++
#define int ll
const int MAXN = 2e5 + 1;
const ll inf = 1e9;
const ld EPS = 1e-4;
const ld PI = acos(-1);
int mod = (int)998244353;
//const int MOD = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const ll MOD = 1000000007;
const int maxelem = 12000000;
const int fsconst = 12000;
vector<int> zf(string s)
{
	vector<int> z(s.size());
	int l = 0, r = -1;
	int n = s.size();
	for (int i = 1; i < s.size(); ++i)
	{
		if (i <= r)
		{
			z[i] = min(r - i + 1, z[i - l]);
		}
		while (i + z[i] < n&& s[i + z[i]] == s[z[i]]) z[i]++;
		if (i + z[i] - 1 > r)
		{
			r = i + z[i] - 1;
			l = i;
		}
	}
	return z;
}
signed main()
{
	fastio();
	int n;
	cin >> n;
	vector<string> a(n);
	vin(a);
	string w = a[0];
	for (int i = 1; i < n; ++i)
	{
		int tsz = min(w.size(), a[i].size());
		string tmp = string(w.begin() + (int)w.size() - tsz, w.end());
		string kek = a[i] + '#' + tmp;
		auto zz = zf(kek);
		int tj = 0;
		for (int i = 0; i < zz.size();++i)
		{
			if (zz[i] + i == kek.size())
			{
				tj = zz[i];
				break;
			}
		}
		w += string(a[i].begin() + tj, a[i].end());
	}
	cout << w;
	//sp;
}