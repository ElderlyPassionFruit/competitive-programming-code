#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
vector<int> have[MAXN];
int n, m;
int c[MAXN];
int fans[MAXN];
int ans[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int sz;
		cin >> sz >> c[i];
		for (int j = 0; j < sz; j++) {
			int x;
			cin >> x;
			have[x - 1].push_back(i);
		}
	}
	for (int i = 0; i < m; i++) {
		if (have[i].empty()) {
			ans[i] = 1;
			continue;
		}
		sort(all(have[i]), [&] (int a, int b) {return c[a] < c[b];});
		ans[i] = c[have[i][0]];
		for (auto x : have[i]) {
			fans[x] = max(fans[x], ans[i]);
		}
	}
	for (int i = 0; i < n; i++) {
		if (fans[i] != c[i]) {
			cout << "Poor memory" << endl;
			return 0;
		}
	}
	cout << "Good memory" << endl;
	for (int i = 0; i < m; i++) {
		cout << ans[i] << " ";
	}
	cout << endl;
	return 0;
}