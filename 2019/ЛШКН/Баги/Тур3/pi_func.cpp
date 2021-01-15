/*
	Prefix function
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
char s[2 * N], p[N];
int pi[2 * N];
int n, m;

void calcPi(int L) {
	for (int i = 1; i < L; i++) {
		int x = pi[i - 1];
		while(x > 0 && s[i] != s[x])
			x = pi[x - 1];
		if (x != 0) {
			pi[i] = x + 1;
		} else if (s[i] == s[0]) {
			pi[i] = 1;
		} else {
			pi[i] = 0;
		}
	}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%s", s);
	scanf("%s", p);
	n = strlen(s);
	m = strlen(p);
	for (int i = n - 1; i >= 0; i--)
		s[m + i] = s[i];
	for (int i = 0; i < m; i++)
		s[i] = p[i];
	calcPi(n + m);
	int ans = 0;
	for (int i = m; i < n + m; i++)
		if (pi[i] == m)
			ans++;
	printf("%d\n", ans);

	return 0;
}
