/*
	Problem K
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

ll c00, c01, c10, c11;

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%lld%lld%lld%lld", &c00, &c01, &c10, &c11);
	ll x = 0, y = 0, z = 0;
	ll sum = c00 + c01 + c10 + c11;
	c00 *= 2;
	c11 *= 2;
	sum *= 2;
	while(x * (x - 1) < c00) x++;
	while(y * (y - 1) < c11) y++;
	while(z * (z - 1) < sum) z++;
	if (x * (x - 1) != c00 || y * (y - 1) != c11 || z * (z - 1) != sum) {
		printf("impossible\n");
		return 0;
	}
	if (z == 0) z = 1;
	if (x == 0) {
		if (x + y != z) x++;
	} else if (y == 0) {
		if (x + y != z) y++;
	}
	if (x + y != z) {
		printf("impossible\n");
		return 0;
	}
	while(x > 0 || y > 0) {
		if (x > 0 && c01 >= y) {
			printf("0");
			x--;
			c01 -= y;
		} else if (y > 0 && c10 >= x) {
			printf("1");
			y--;
			c10 -= x;
		} else throw;
	}
	printf("\n");

	return 0;
}
