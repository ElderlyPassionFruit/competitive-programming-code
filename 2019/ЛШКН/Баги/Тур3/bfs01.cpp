/*
	01-BFS
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
vector<pii> g[N];
vector<int> q[N];
int dist[N];
int n, m;

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &m);
	while(m--) {
		int v, u, w;
		// w \in {0,1}
		scanf("%d%d%d", &v, &u, &w);
		v--;u--;
		g[v].push_back(mp(u, w));
		g[u].push_back(mp(v, w));
	}
	for (int v = 0; v < n; v++)
		dist[v] = N;
	dist[0] = 0;
	q[0].push_back(0);
	for (int d = 0; d < n; d++) {
		for (int v : q[d]) {
			if (dist[v] != d) continue;
			for (pii e : g[v]) {
				int u = e.first;
				if (dist[u] <= dist[v] + e.second) continue;
				dist[u] = dist[v] + e.second;
				q[dist[u]].push_back(u);
			}
		}
	}
	printf("%d\n", dist[n - 1]);

	return 0;
}
