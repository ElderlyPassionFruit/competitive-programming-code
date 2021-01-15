/*
	Cycle detection
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
bool used[N];
int par[N];

void dfs(int v) {
	used[v] = 1;
	for (int u : g[v]) {
		if (used[u] == 0) {
			par[u] = v;
			dfs(u);
		} else if (used[u] == 2) {
			int w = u;
			while(w != v) {
				printf("%d ", w + 1);
				w = par[w];
			}
			printf("%d\n", w + 1);
			exit(0);
		}
	}
	used[v] = 2;
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
		if (used[v]) continue;
		dfs(v);
	}
	printf("no cycles\n");

	return 0;
}
