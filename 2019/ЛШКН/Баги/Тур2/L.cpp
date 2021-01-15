/*
	Problem L
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <vector>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <cassert>
#include <complex>
#include <string>
#include <cstring>
#include <chrono>
#include <random>
#include <queue>
#include <bitset>
using namespace std;

#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef long double ld;
#define mp make_pair
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

const ll MOD = (ll)1e9 + 7;
ll add(ll x, ll y) {
	x += y;
	if (x >= MOD) return x - MOD;
	return x;
}
ll sub(ll x, ll y) {
	x -= y;
	if (x < 0) return x + MOD;
	return x;
}
ll mult(ll x, ll y) {
	return (x * y) % MOD;
}

const int N = 100100;
ll c[N];
vector<int> d[N];
ll a[N];

void precalc() {
	for (int x = 1; x < N; x++)
		for (int y = x; y < N; y += x)
			d[y].push_back(x);
	c[1] = 1;
	for (int x = 2; x < N; x++)
		c[x] = sub(0, mult(c[MOD % x], MOD / x));
	for (int x = 2; x < N; x++)
		for (int y : d[x])
			if (y != x)
				c[x] = sub(c[x], c[y]);
}

void solve() {
	int mx = 0;
	a[mx] = 0;
	int n;
	scanf("%d", &n);
	while(n--) {
		int x;
		scanf("%d", &x);
		while(mx < x) a[++mx] = 0;
		for (int y : d[x])
			a[y] += x;
	}
	ll ans = 0;
	for (int i = 1; i <= mx; i++)
		ans = add(ans, mult(c[i], mult(a[i], a[i])));
	printf("%lld\n", ans);
}

int main()
{
	freopen("lcm.in", "r", stdin);
//	freopen("output.txt", "w", stdout);

	precalc();

	int t;
	scanf("%d", &t);
	while(t--) solve();

	return 0;
}
