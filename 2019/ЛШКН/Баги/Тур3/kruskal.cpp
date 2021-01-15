/*
	Kruskal
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
int n;
int par[N];
vector<int> a[N];

struct Edge {
	int v, u, w;

	Edge() : v(), u(), w() {}

	void scan() {
		scanf("%d%d%d", &v, &u, &w);
		v--;u--;
	}

	bool operator < (const Edge &e) const {
		return w < e.w;
	}
};
Edge ed[N];
int m;

bool unite(int v, int u) {
	v = par[v];
	u = par[u];
	if (v == u) return false;
	if ((int)a[v].size() < (int)a[u].size()) swap(v, u);
	for (int w : a[u])
		a[v].push_back(w);
	return true;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		par[i] = i;
		a[i].push_back(i);
	}
	for (int i = 0; i < m; i++)
		ed[i].scan();
	sort(ed, ed + m);
	ll cost = 0;
	for (int i = 0; i < m; i++) {
		if (unite(ed[i].v, ed[i].u)) {
			n--;
			cost += ed[i].w;
		}
	}
	if (n != 1)
		printf("not connected\n");
	else
		printf("%lld\n", cost);

	return 0;
}
