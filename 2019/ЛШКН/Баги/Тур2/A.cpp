/*
	Problem A
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

const int N = 1111;
int n;
int sz;
int a[N], b[N];
int ANS = 0;

int query(int id, int k) {
	printf("? %d %d\n", id, k);
	int x;
	scanf("%d", &x);
	return x;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		a[sz++] = i;
	for (int k = 0; sz > 0; k++) {
		int c0 = 0, c1 = 0;
		for (int i = 0; i < sz; i++) {
			b[i] = query(a[i], k);
			if (b[i] == 0)
				c0++;
			else
				c1++;
		}
		int tot = ((n - ANS) >> k) + 1;
		if (sz != tot - 1) throw;
		int w1 = tot / 2;
		int w0 = tot - w1;
		if (c0 > w0 || c1 > w1) throw;
		int g = 0;
		if (c0 < w0) {
			g = 0;
		} else {
			g = 1;
		}
		ANS |= g << k;
		int nsz = 0;
		for (int i = 0; i < sz; i++)
			if (b[i] == g)
				a[nsz++] = a[i];
		sz = nsz;
	}
	printf("! %d\n", ANS);

	return 0;
}
