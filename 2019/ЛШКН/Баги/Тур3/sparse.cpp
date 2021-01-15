/*
	Sparse Table
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

const int N = 100100;
const int LOG = 17;
int sparse[LOG][N];
int p2[N];
int n;

int getMin(int l, int r) {
	int k = p2[r - l];
	return min(sparse[k][l], sparse[k][r - (1 << k)]);
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	for (int i = 2; i < N; i++)
		p2[i] = p2[i / 2] + 1;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &sparse[0][i]);
	for (int k = 0; k < LOG - 1; k++) {
		for (int i = 0; i + (1 << (k + 1)) < n; i++)
			sparse[k + 1][i] = min(sparse[k][i], sparse[k][i + (1 << k)]);
	}
	int q;
	scanf("%d", &q);
	while(q--) {
		int l, r;
		scanf("%d%d", &l, &r);
		l--;
		printf("%d\n", getMin(l, r));
	}

	return 0;
}
