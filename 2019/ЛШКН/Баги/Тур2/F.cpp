/*
	Problem F
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
const int M = 52;
const int A = 26;
char s[N];
char p[M];
int a[M][A];
int b[M][A];
int pi[M];
int n, m, k;
int dp[N][M][M];

void buildAut() {
	for (int i = 1; i < m; i++) {
		pi[i] = 0;
		int x = pi[i - 1];
		while(x > 0 && p[x] != p[i]) x = pi[x - 1];
		if (x > 0) {
			pi[i] = x + 1;
		} else if (p[i] == p[0])
			pi[i] = 1;
	}
	for (int i = 0; i <= m; i++)
		for (int c = 0; c < A; c++) {
			int x = i;
			while(x > 0 && (x == m || p[x] != (char)('a' + c))) x = pi[x - 1];
			if (x > 0) {
				a[i][c] = x + 1;
			} else if (p[0] == (char)('a' + c)) {
				a[i][c] = 1;
			} else {
				a[i][c] = 0;
			}
		}
}

int main()
{
//	freopen("input.txt", "r", stdin);
//	freopen("output.txt", "w", stdout);

	scanf("%s%s", s, p);
	n = strlen(s);
	m = strlen(p);
	buildAut();
	for (int i = 0; i <= m; i++)
		for (int c = 0; c < A; c++)
			b[i][c] = a[i][c];
	scanf("%s", p);
	k = m;
	m = strlen(p);
	buildAut();

//	cerr << "here" << endl;

	for (int i = 0; i <= n; i++)
		for (int j = 0; j <= m; j++)
			for (int h = 0; h <= k; h++)
				dp[i][j][k] = (i < n ? -N : 0);

	for (int i = n - 1; i >= 0; i--)
		for (int x = 0; x <= m; x++)
			for (int y = 0; y <= k; y++) {
				for (int c = 0; c < A; c++) {
					if (s[i] != '*' && s[i] != ((char)('a' + c))) continue;
					int nx = a[x][c], ny = b[y][c];
					int cur = dp[i + 1][nx][ny];
					if (nx == m) cur--;
					if (ny == k) cur++;
					dp[i][x][y] = max(dp[i][x][y], cur);
				}
			}

	int x = 0, y = 0;
	for (int i = 0; i < n; i++) {
		bool ok = false;
		for (int c = 0; !ok && c < A; c++) {
			if (s[i] != '*' && s[i] != ((char)('a' + c))) continue;
			int nx = a[x][c], ny = b[y][c];
			int cur = dp[i + 1][nx][ny];
			if (nx == m) cur--;
			if (ny == k) cur++;
			if (cur > dp[i][x][y]) throw;
			if (cur < dp[i][x][y]) continue;
			s[i] = (char)('a' + c);
			x = nx;
			y = ny;
			ok = true;
		}
		if (!ok) throw;
	}
	printf("%s\n", s);

	return 0;
}
