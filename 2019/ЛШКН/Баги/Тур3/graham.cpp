/*
	Graham
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

struct Point {
	ll x, y;

	Point() : x(), y() {}
	Point (ll _x, ll _y) : x(_x), y(_y) {}

	void scan() {
		scanf("%lld%lld", &x, &y);
	}

	Point operator + (const Point &a) const {
		return Point(x + a.x, y + a.y);
	}
	Point operator - (const Point &a) const {
		return Point(x - a.x, y - a.y);
	}
	Point operator * (const ll &k) const {
		return Point(x * k, y * k);
	}
	ll operator % (const Point &a) const {
		return x * a.x + y * a.y;
	}
	ll operator * (const Point &a) const {
		return x * a.y - y * a.x;
	}
	ll sqrLen() const {
		return *this % *this;
	}

	bool operator < (const Point &a) const {
		if (x != a.x) return x < a.x;
		return y < a.y;
	}
};

const int N = 100100;
int n;
Point a[N];
Point minP;

bool cmp(const Point &a, const Point &b) {
	Point v = a - minP, u = b - minP;
	ll x = v * u;
	if (x != 0) return x > 0;
	return v.sqrLen() < u.sqrLen();
}

void graham() {
	minP = a[0];
	for (int i = 0; i < n; i++)
		minP = min(minP, a[i]);
	sort(a, a + n, cmp);
	int m = 1;
	for (int i = 1; i < n; i++) {
		while(m >= 2 && (a[i] - a[m - 1]) * (a[m - 1] - a[m - 2]) >= 0) m--;
		a[m++] = a[i];
	}
	n = m;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		a[i].scan();
	graham();
	ll S = 0;
	for (int i = 0; i < n; i++)
		S += a[i] * a[i + 1];
	printf("%lld.%lld\n", S / 2, (S & 1) * 5);

	return 0;
}
