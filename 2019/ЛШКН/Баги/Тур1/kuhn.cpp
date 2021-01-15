/*
	Kuhn
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

const int N = 1010;
vector<int> g[N];
int mt[N];
bool used[N];
int n, m;
char s[N];

bool dfs(int x) {
	if (used[x]) return false;
	used[x] = true;
	for (int y : g[x]) {
		if (mt[y] == -1 || dfs(mt[y])) {
			mt[y] = x;
			return true;
		}
	}
	return false;
}
int kuhn() {
	int res = 0;
	for (int i = 0; i < n; i++)
		mt[i] = -1;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++)
			used[j] = 0;
		if (dfs(i))
			res++;
	}
	return res;
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) {
		scanf("%s", s);
		for (int j = 0; j < m; j++)
			if (s[j] == '1')
				g[i].push_back(j);
	}
	printf("%d\n", kuhn());

	return 0;
}
