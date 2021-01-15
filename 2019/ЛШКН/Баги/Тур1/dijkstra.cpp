/*
	Dijkstra
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

const int INF = (int)1e9;
const int N = 100100;
int n, m;
vector<pii> g[N];
int dist[N];
set<pii> setik;

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &m);
	while(m--) {
		int v, u, w;
		scanf("%d%d%d", &v, &u, &w);
		v--;u--;
		g[v].push_back(mp(u, w));
		g[u].push_back(mp(v, w));
	}
	for (int v = 0; v < n; v++)
		dist[v] = INF;
	dist[0] = 0;
	for (int v = 0; v < n; v++)
		setik.insert(mp(v, dist[v]));
	while(!setik.empty()) {
		int v = setik.begin()->first;
		setik.erase(setik.begin());
		for (pii e : g[v]) {
			int u = e.first;
			int w = dist[v] + e.second;
			if (dist[u] <= w) continue;
			setik.erase(mp(u, dist[u]));
			dist[u] = w;
			setik.insert(mp(u, dist[u]));
		}
	}
	printf("%d\n", dist[n - 1]);

	return 0;
}
