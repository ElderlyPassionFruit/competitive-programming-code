/*
	Secret Graph Problem (secret1)
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
vector<int> g[N];
int dist[N];
int q[N];
int topQ;

void BFS(int v) {
	topQ = 0;
	for (int i = 0; i < n; i++)
		dist[i] = N;
	dist[v] = 0;
	q[topQ++] = v;
	for (int i = 0; i < topQ; i++) {
		v = q[i];
		for (int u : g[v]) {
			if (dist[u] <= dist[v] + 1) continue;
			dist[u] = dist[v] + 1;
			q[topQ++] = u;
		}
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		int v, u;
		scanf("%d%d", &v, &u);
		v--;u--;
		g[v].push_back(u);
		g[u].push_back(v);
	}
	BFS(0);
	if (topQ != n) throw;
	BFS(q[topQ - 1]);
	printf("%d %d\n", q[0] + 1, q[topQ - 1] + 1);

	return 0;
}
