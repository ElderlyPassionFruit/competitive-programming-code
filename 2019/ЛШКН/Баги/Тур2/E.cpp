/*
	Problem E
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

const int N = 2020;
const int M = 4020;
const int LOG = 11;
char s[N][M];
int n, m, q;
int p[N];
int rev[N];
int sparse[LOG][N];
int p2[N];
int a[N];
int ans[N];

int getMin(int l, int r) {
	int k = p2[r - l];
	return min(sparse[k][l], sparse[k][r - (1 << k)]);
}

bool cmp(const int &v, const int &u) {
	if (v == u) return false;
	int x = 0;
	while(s[v][x] == s[u][x]) x++;
	return s[v][x] < s[u][x];
}

void precalc() {
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 0; i < n; i++)
		scanf("%s", s[i]);
	for (int i = 0; i < n; i++)
		p[i] = i;
	sort(p, p + n, cmp);
	for (int i = 0; i < n; i++)
		rev[p[i]] = i;
	for (int i = 0; i < n - 1; i++) {
		int r = p[i], w = p[i + 1];
		int lcp = 0;
		while(s[r][lcp] == s[w][lcp]) lcp++;
		sparse[0][i] = lcp;
	}
	for (int k = 0; k < LOG; k++) {
		for (int i = 0; i + (1 << k) < n; i++)
			sparse[k + 1][i] = min(sparse[k][i], sparse[k][i + (1 << k)]);
	}
}

void solve() {
	precalc();
	while(q--) {
		int k;
		scanf("%d", &k);
		for (int i = 0; i < k; i++) {
			int x;
			scanf("%d", &x);
			a[i] = rev[x];
		}
		sort(a, a + k);
		for (int i = 0; i < k - 1; i++)
			ans[i] = getMin(a[i], a[i + 1]);
		k--;
		sort(ans, ans + k);
		k = unique(ans, ans + k) - ans;
		printf("%d", k);
		for (int i = 0; i < k; i++)
			printf(" %d", ans[i]);
		printf("\n");
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	for (int i = 2; i < N; i++)
		p2[i] = p2[i / 2] + 1;

	int t;
	scanf("%d", &t);
	for (int i = 1; i <= t; i++) {
		printf("Case #%d:\n", i);
		solve();
	}

	return 0;
}
