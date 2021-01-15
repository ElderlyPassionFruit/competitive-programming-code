#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 10;
pair<int, int> ed[MAXN];
int n;
int p[MAXN];
int a[MAXN];
int ans[MAXN];
int fans[MAXN];
int help[MAXN];

void relax() {
	for (int i = 0; i < n; i++)
		fans[help[i]] = i;
	bool flag = false;
	for (int i = 0; i < n; i++) {
		if (ans[i] < fans[i]) return;
		flag = ans[i] > fans[i];
		if (flag) break;
	}
	if (flag) {
		for (int i = 0; i < n; i++)
			ans[i] = fans[i];
	}
}

void recalc() {
	for (int i = 0; i < n; i++) {
		help[i] = p[i];
	}
	for (int i = 0; i < n - 1; i++) 
		swap(help[ed[a[i]].first], help[ed[a[i]].second]);
	
	relax();
}

void solve() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		x--;
		p[x] = i;
	}
	for (int i = 0; i < n - 1; i++) {
		cin >> ed[i].first >> ed[i].second;
		ed[i].first--; ed[i].second--;
	}

	for (int i = 0; i < n - 1; i++)
		a[i] = i;

	for (int i = 0; i < n; i++)
		ans[i] = n;

	do {
		recalc();
	} while (next_permutation(a, a + n - 1));

	for (int i = 0; i < n; i++)
		cout << ans[i] + 1 << " ";
	cout << "\n"; 
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}