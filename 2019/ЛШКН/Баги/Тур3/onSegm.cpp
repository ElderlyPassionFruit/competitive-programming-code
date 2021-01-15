/*
	Points on segment
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
};

bool onSegm(Point A, Point B, Point C) {
	return (A - B) % (C - B) == 0 && (A - B) * (C - B) > 0 && (A - B) % (A - B) >= (C - B) % (C - B);
}

const int N = 505;
Point a[N];
int n;

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		a[i].scan();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int ans = 0;
			for (int h = 0; h < n; h++)
				ans += (int)onSegm(a[i], a[h], a[j]);
			printf("%d ", ans);
		}
		printf("\n");
	}

	return 0;
}
