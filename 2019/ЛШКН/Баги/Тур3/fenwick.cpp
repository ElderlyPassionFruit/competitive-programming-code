/*
	Fenwick tree
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

const int N = (int)1e6 + 7;
int fenv[N];

void addFenv(int p, int x) {
	for(; p < N; p |= p + 1)
		fenv[p] += x;
}
int getFenv(int r) {
	int res = 0;
	for(; r > 0; r &= r - 1)
		res += fenv[r];
	return res;
}

int n;

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	ll ans = 0;
	for (int i = 0; i < n; i++) {
		int x;
		scanf("%d", &x);
		ans += getFenv(n) - getFenv(x);
		addFenv(x, 1);
	}
	printf("%lld\n", ans);

	return 0;
}
