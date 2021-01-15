/*
	Problem G
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

const int K = 20;
const int N = 600600;
int n;
int a[N];
int b[K];
int c[K];

bool solve(int k) {
	for (int i = 0; i < k; i++)
		b[i] = -1;
	int sz = 0;
	for (int j = 0; j < n; j++) {
		int x = a[j];
		if (x >= (1 << k)) continue;
		for (int i = 0; i < k; i++) {
			if (((x >> i) & 1) == 0) continue;
			if (b[i] == -1) {
				b[i] = x;
				c[sz++] = a[j];
				break;
			} else x ^= b[i];
		}
	}
	if (sz < k) return false;
	printf("%d\n", k);
	for (int i = 0; i < (1 << k); i++) {
		int mask = i ^ (i >> 1);
		int x = 0;
		for (int j = 0; j < k; j++)
			if ((mask >> j) & 1)
				x ^= b[j];
		printf("%d ", x);
	}
	printf("\n");
	return true;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	for (int k = K - 1; k >= 0; k--) {
		if (solve(k)) return 0;
	}
	throw;
	return 0;
}
