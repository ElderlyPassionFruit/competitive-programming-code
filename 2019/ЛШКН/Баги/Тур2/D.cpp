/*
	Problem D
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


const int M = 10100;
int fenv[M];
void addFenv(int p, int dx) {
	for(;p < M; p |= p + 1)
		fenv[p] += dx;
}
int getFenv(int r) {
	int res = 0;
	for(; r >= 0; r = (r & (r + 1)) - 1)
		res += fenv[r];
	return res;
}
int getSum(int l, int r) {
	return getFenv(r - 1) - getFenv(l - 1);
}

int n;
int a[M][2];
ll xs[M];
int xsSz;
ll b[4 * M][4];
int sum[4 * M];
int ans[M];

struct Event {
	int t;
	ll x;
	int id;

	Event() : t(), x(), id() {}
	Event(int _t, ll _x, int _id) : t(_t), x(_x), id(_id) {}

	bool operator < (const Event &e) const {
		if (x != e.x) return x < e.x;
		return t < e.t;
	}
};
Event ev[9 * M];
int evSz;

void solve2(ll C) {
	xsSz = 0;
	for (int i = 0; i < n; i++) {
		xs[xsSz++] = a[i][1];
	}
	sort(xs, xs + xsSz);
	xsSz = unique(xs, xs + xsSz) - xs;
	for (int i = 0; i < n; i++) {
		ll x = a[i][0], y = a[i][1];
		b[4 * i + 0][0] = b[4 * i + 1][0] = x;
		b[4 * i + 0][1] = b[4 * i + 1][1] = x + C;
		b[4 * i + 2][0] = b[4 * i + 3][0] = x - C + 1;
		b[4 * i + 2][1] = b[4 * i + 3][1] = x + 1;
		b[4 * i + 0][2] = b[4 * i + 2][2] = y;
		b[4 * i + 0][3] = b[4 * i + 2][3] = y + C;
		b[4 * i + 1][2] = b[4 * i + 3][2] = y - C + 1;
		b[4 * i + 1][3] = b[4 * i + 3][3] = y + 1;
	}
	for (int i = 0; i < 4 * n; i++)
		for (int j = 2; j < 4; j++)
			b[i][j] = lower_bound(xs, xs + xsSz, b[i][j]) - xs;
	memset(fenv, 0, sizeof fenv);
	evSz = 0;
	for (int i = 0; i < n; i++) {
		ev[evSz++] = Event(1, a[i][0], i);
	}
	for (int i = 0; i < 4 * n; i++) {
		ev[evSz++] = Event(0, b[i][0], i);
		ev[evSz++] = Event(0, b[i][1], i);
		sum[i] = 0;
	}
	sort(ev, ev + evSz);
	for (int j = 0; j < evSz; j++) {
		Event e = ev[j];
		if (e.t == 0) {
			if (e.x == b[e.id][0]) {
				sum[e.id] -= getSum(b[e.id][2], b[e.id][3]);
			} else {
				sum[e.id] += getSum(b[e.id][2], b[e.id][3]);
			}
		} else {
			int y = lower_bound(xs, xs + xsSz, a[e.id][1]) - xs;
			addFenv(y, 1);
		}
	}
	memset(fenv, 0, sizeof fenv);
	evSz = 0;
	for (int i = 0; i < n; i++) {
		ev[evSz++] = Event(1, a[i][0], i);
	}
	for (int i = 0; i < 4 * n; i++) {
		if (sum[i] < 3) continue;
		ev[evSz++] = Event(0, b[i][0], i);
		ev[evSz++] = Event(0, b[i][1], i);
	}
	sort(ev, ev + evSz);
	for (int j = 0; j < evSz; j++) {
		Event e = ev[j];
		if (e.t == 0) {
			if (e.x == b[e.id][0]) {
				addFenv(b[e.id][2], 1);
				addFenv(b[e.id][3], -1);
			} else {
				addFenv(b[e.id][2], -1);
				addFenv(b[e.id][3], 1);
			}
		} else {
			int y = lower_bound(xs, xs + xsSz, a[e.id][1]) - xs;
			if (getFenv(y) > 0)
				ans[e.id] = 1;
		}
	}
}

bool solve(ll C) {
	for (int i = 0; i < n; i++)
		ans[i] = 0;
	solve2(C);
	for (int i = 0; i < n; i++)
		if (!ans[i])
			return false;
	return true;
}

int main()
{
//	freopen("input.txt", "r", stdin);
	freopen("big.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < 2; j++)
			scanf("%d", &a[i][j]);
	ll l = 0, r = (ll)2e9 + 5;
	while(r - l > 1) {
		ll x = (l + r) / 2;
		if (solve(x))
			r = x;
		else
			l = x;
	}
	printf("%lld\n", l);

	return 0;
}
