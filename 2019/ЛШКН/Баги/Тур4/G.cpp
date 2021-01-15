/*
	Problem G
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
using namespace std;
 
#ifdef LOCAL
	#define eprintf(...) fprintf(stderr, __VA_ARGS__)
#else
	#define eprintf(...) 42
#endif
 
typedef long long ll;
typedef pair<int, int> pii;
#define mp make_pair
 
struct Edge
{
	int v, u, id;
 
	Edge() : v(), u(), id() {}
	Edge (int _v, int _u, int _id) : v(_v), u(_u), id(_id) {}
};
 
const int N = 100100;
int par[N], sz[N];
int n, m, k;
Edge a[N], b[N];
bool take[N];
 
void read()
{
	int q;
	scanf("%d%d", &n, &q);
	for (int i = 0; i < q; i++) {
		int v, u;
		char c;
		scanf("%d%d %c", &v, &u, &c);
		v--;u--;
		if (c == 'S')
			a[m++] = Edge(v, u, i + 1);
		else
			b[k++] = Edge(v, u, i + 1);
	}
}
 
int getPar(int v)
{
	return par[v] == -1 ? v : par[v] = getPar(par[v]);
}
bool unite(int v, int u)
{
	v = getPar(v); u = getPar(u);
	if (v == u) return false;
	if (sz[v] < sz[u]) swap(v, u);
	sz[v] += sz[u];
	par[u] = v;
	return true;
}
 
int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);
 
	read();
	if (n % 2 == 0) {
		printf("-1\n");
		return 0;
	}
	for (int i = 0; i < n; i++) {
		par[i] = -1;
		sz[i] = 1;
	}
	int C = 0;
	for (int i = 0; i < m; i++) {
		if (unite(a[i].v, a[i].u))
			C++;
	}
	if (2 * C + 1 < n) {
		printf("-1\n");
		return 0;
	}
	for (int i = 0; i < k; i++) {
		if (unite(b[i].v, b[i].u)) {
			take[i] = 1;
			C++;
		}
	}
	if (C + 1 != n) {
		printf("-1\n");
		return 0;
	}
	C = 0;
	for (int i = 0; i < n; i++) {
		par[i] = -1;
		sz[i] = 1;
	}
	for (int i = 0; i < k; i++) {
		if (!take[i]) continue;
		C++;
		unite(b[i].v, b[i].u);
	}
	for (int i = 0; 2 * C + 1 < n && i < k; i++) {
		if (take[i]) continue;
		if (unite(b[i].v, b[i].u)) {
			C++;
			take[i] = 1;
		}
	}
	if (2 * C + 1 < n) {
		printf("-1\n");
		return 0;
	}
	printf("%d\n", n - 1);
	for (int i = 0; i < k; i++) {
		if (unite(a[i].v, a[i].u))
			printf("%d ", a[i].id);
	}
	for (int i = 0; i < m; i++)
		if (take[i])
			printf("%d ", b[i].id);
	printf("\n");
 
	return 0;
}