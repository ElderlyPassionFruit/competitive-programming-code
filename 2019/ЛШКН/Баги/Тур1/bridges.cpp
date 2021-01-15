/*
	bridges
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
int n, m;
vector<int> g[N];
int h[N];
int minH[N];
int bridges;

void dfs(int v, int par) {
	minH[v] = h[v];
	for (int u : g[v]) {
		if (h[u] == -1) {
			h[u] = h[v] + 1;
			dfs(u, v);
			minH[v] = min(minH[v], minH[u]);
		} else {
			minH[v] = min(minH[v], h[u]);
		}
	}
	if (par != -1 && minH[v] > h[par])
		bridges++;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &m);
	while(m--) {
		int v, u;
		scanf("%d%d", &v, &u);
		v--;u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	for (int v = 0; v < n; v++) {
		h[v] = -1;
	}
	h[0] = 0;
	dfs(0, -1);
	printf("%d\n", bridges);

	return 0;
}
