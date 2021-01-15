#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,abm,mmx,avx,avx2,tune=native,popcnt")
//#pragma GCC optimize("-O3")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
const int MAXN = 2e5 + 10;
int dp[MAXN];
int n, a[MAXN];
unordered_map<int, int> pos;
const int INF = 2e9 + 228;

inline int calc(int d) {
	if(1ll * d * (n-1) > a[n  * 2 -1] - a[0]) return INF;
	for (int i = 0; i < 2 * n; i++) {
		dp[i] = 1;
		if (pos.count(a[i] - d)) {
			dp[i] = max(dp[i], dp[pos[a[i] - d]] + 1);
		}
		if(dp[i]>=n)
		{
			return a[i] - (n-1) * d;
		}
	}
	return INF;
}

unordered_map<int, int> cnt;

mt19937 rnd(time(0));

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);

	freopen("arithm.in", "r", stdin);
	freopen("arithm.out", "w", stdout);
	scanf("%d", &n);

	for (int i = 0; i < 2 * n; i++) {
		scanf("%d",&a[i]);
		cnt[a[i]]++;
	}

	for (auto i : cnt) {
		if (i.second >= n) {
			cout << i.first << " " << 0 << endl;
			return 0;
		}
	}
	sort(a, a + 2 * n);
	for (int i = 0; i < 2 * n; i++) {
		pos[a[i]] = i;
	}
	int iters = 0;
	set<int> used;
	while (true) {
		int pos1 = rnd() % (2 * n);
		int pos2 = rnd() % (2 * n);
		if (pos1 > pos2) swap(pos1, pos2);
		if (a[pos2] - a[pos1] == 0) continue;
		iters++;
		if(iters> 10)
		{
			assert(0);
		}
		int d = a[pos2] - a[pos1];
		for (int i = 1; i * i <= d; i++) {
			if (d % i == 0) {
				if (!used.count(i)) {
					int x = calc(i);
					if (x != INF) {
						cout << x << " " << i << endl;
						return 0;
					}
					used.insert(i);
				}
				if (!used.count(d / i)) {
					int x = calc(d / i);
					if (x != INF) {
						cout << x << " " << d / i << endl;
						return 0;
					}
					used.insert(d / i);
				}	
			}
		}
 	}
	return 0;
}