#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e3 + 10;
int a[MAXN][MAXN];
int n, m;
bool used[MAXN][MAXN];
int ans;

void solve(int x, int y) {
	if (used[x][y]) return;
	vector<pair<int, int>> have;
	have.push_back({x, y});
	have.push_back({n - 1 - x, y});
	have.push_back({x, m - 1 - y});
	have.push_back({n - 1 - x, m - 1 - y});
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	vector<int> fans;
	for (auto [x, y] : have) {
		assert(!used[x][y]);
		used[x][y] = true;
		fans.push_back(a[x][y]);
	}
	sort(all(fans));
	int cnt_ans = 0;
	int now = 1;
	for (int i = 1; i < (int)fans.size(); i++) {
		if (fans[i] == fans[i - 1]) {
			now++;
		} else {
			cnt_ans = max(cnt_ans, now);
			now = 1;
		}
	}
	cnt_ans = max(cnt_ans, now);
	ans += fans.size() - cnt_ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> a[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			solve(i, j);
		}
	}
	cout << ans << endl;
	return 0;
}