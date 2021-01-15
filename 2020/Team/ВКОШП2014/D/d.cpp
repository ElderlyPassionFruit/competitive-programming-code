#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
vector<int> a;

bool check(int x, int k) {
	int have = 0;
	vector<bool> used(x + 1);
	for (auto i : a) {
		if (i > x) continue;
		if (used[i]) continue;
		if (i > x - k - have) {
			used[i] = true;
			have++;
		}
	}
	return have == x;
} 

void solve() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	reverse(all(a));
	int l = 0, r = m + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid, k)) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	cout << l << "\n";
	a.clear();
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}

/*
3
4 3 1
3 2 1 2
1 2 1
2 
5 5 2
4 2 1 4 3

*/