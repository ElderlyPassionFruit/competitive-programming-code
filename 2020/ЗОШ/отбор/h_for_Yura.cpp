//#pragma GCC target("sse,sse2,sse3,ssse3,sse4,abm,mmx,avx,avx2,popcnt,tune=native")
//#pragma GCC optimize("SEX_ON_THE_BEACH")	
//#pragma GCC optimize("fast-math")
//#pragma GCC optimize("unroll-loops")
//#pragma comment(linker, "/STACK:36777216")
 
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
#define endl '\n'
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
const ld PI = acos(-1);
int mod = (int)998244353;
const int MOD7 = 1000000007;
const int MOD9 = 1000000009;
const int a228 = 18;
const ll kekmod = 1791791791;
const ll bestmod = 1148822869;
vector<ll> mods = { kekmod,bestmod,mod,MOD9,1000000007 };
vector<ll> hashpows = { 29,31,37,43,47,53,179,229 };
mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count() + 228 + 'i' + 'q' + 1337 + 1488);
ll MOD = mods[rnd() % mods.size()];
ll hashpow = hashpows[rand() % hashpows.size()];
#define int ll

vector<int> zf(string kek) 
{
	int n = kek.size();
	vector<int> z(n);
	int l=0,r=-1;
	for (int i = 1; i < n; ++i)
	{
		if (r>=i) z[i] = min(z[i - l], r - i + 1);
		while (i + z[i] < n && kek[i + z[i]] == kek[z[i]])
			z[i]++;
		if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
	}
	return z;
}

signed main()
{
	int n;
	string kek;
	cin >> kek; n = kek.size();
	vector<int> cnt(n), musorka(n);
	vector<int> z = zf(kek);
	int cc = 0;
	for (int i = 1; i < n; ++i) 
	{
		cnt[i] += cc;
		if (z[i] == 0)
		{
			cc += musorka[i];
			continue;
		}
		cc++;
		cnt[i]++;
		musorka[i + z[i] - 1]--;
		cc += musorka[i];
	}
	int ans = 0;
	int ansos = 0;
	for (int i = 0; i < n; ++i)
	{
		if (cnt[i]>ansos) ans = i;
		ansos = max(ansos, cnt[i]);
	}
	for (int i = 0; i <= ans; ++i)
		cout << kek[i];
	//sp;
}