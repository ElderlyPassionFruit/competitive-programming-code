/*
	Problem C
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

const int N = 200200;
int n;
int a[N];
int b[N];
int c[N];
pii d[N];
int ans[N][2];
int ansSz;

void addAns(int v, int u) {
	ans[ansSz][0] = v;
	ans[ansSz][1] = u;
	ansSz++;
}

void solve() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	int k = 0, m = 0;
	for (int i = 0; i < n; i++) {
		scanf("%d", &b[i]);
		a[i] -= b[i];
		if (b[i] > 0)
			c[k++] = i;
		else
			d[m++] = mp(a[i], i);
	}
	ansSz = 0;
	for (int i = 0; i < k; i++) {
		int v = c[i];
		if (b[v] >= k) {
			printf("-1\n");
			return;
		}
		int u = c[(i == 0 ? k - 1 : i - 1)];
		addAns(u, v);
		b[v]--;
		for (int j = 0; b[v] > 0 && j < k; j++) {
			if (j == i || c[j] == u) continue;
			addAns(c[j], v);
			b[v]--;
		}
	}
	sort(d, d + m);
	set<int> setik;
	for (int v = 0; v < n; v++) {
		if (a[v] > 0)
			setik.insert(v);
	}
	for (int i = 0; i < m; i++) {
		int v = d[i].second;
		if (a[v] > 0) {
			printf("-1\n");
			return;
		}
		auto it = setik.begin();
		while(it != setik.end()) {
			int u = *it;
			addAns(v, u);
			a[u]--;
			if (a[u] == 0)
				it = setik.erase(it);
		}
	}
	if (!setik.empty()) {
		printf("-1\n");
		return;
	}
	printf("%d\n", ansSz);
	for (int i = 0; i < ansSz; i++)
		printf("%d %d\n", ans[i][0] + 1, ans[i][1] + 1);
}

int main()
{
	freopen("topo.in", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int t;
	scanf("%d", &t);
	while(t--) solve();

	return 0;
}
