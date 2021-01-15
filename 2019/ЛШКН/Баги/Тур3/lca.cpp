/*
	LCA via binary lifts
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
vector<int> g[N];
int h[N];
int par[N][LOG];

void dfs(int v) {
	for (int u : g[v]) {
		if (h[u] != -1) continue;
		h[u] = h[v] + 1;
		par[u][0] = v;
		for (int k = 0; k < LOG - 1; k++) {
			int w = par[u][k];
			if (w == -1) break;
			par[u][k + 1] = par[w][k];
		}
		dfs(u);
	}
}

int up(int v, int dh) {
	for (int k = LOG - 1; k >= 0; k--) {
		if (dh < (1 << k)) continue;
		dh -= 1 << k;
		v = par[v][k];
	}
	return v;
}
int LCA(int v, int u) {
	if (h[v] > h[u]) swap(v, u);
	u = up(u, h[u] - h[v]);
	for (int k = LOG - 1; k >= 0; k--) {
		if (par[v][k] != par[u][k]) {
			v = par[v][k];
			u = par[u][k];
		}
	}
	return par[v][0];
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	int n;
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		int v, u;
		scanf("%d%d", &v, &u);
		v--;u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	for (int v = 0; v < n; v++) {
		h[v] = -1;
		for (int k = 0; k < LOG; k++)
			par[v][k] = -1;
	}
	h[0] = 0;
	dfs(0);
	int q;
	scanf("%d", &q);
	while(q--) {
		int v, u;
		scanf("%d%d", &v, &u);
		v--;u--;
		printf("%d\n", h[v] + h[u] - 2 * h[LCA(v, u)]);
	}

	return 0;
}
