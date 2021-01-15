#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e3 + 10;
int n, m;
char a[MAXN][MAXN];

bool checkCell(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < m && a[x][y] == '*';
}

vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};

int get(int x, int y, int it) {
	if (!checkCell(x, y)) return 0;
	return get(x + dx[it], y + dy[it], it) + 1;
}

bool check(int x, int y) {
	if (!checkCell(x, y)) return false;
	for (int i = 0; i < 4; i++) {
		if (!checkCell(x + dx[i], y + dy[i])) {
			return false;
		}
	}
	int ans = get(x, y, 0);
	for (int i = 1; i < 4; i++) {
		if (get(x, y, i) != ans) {
			return false;
		}
	}
	return true;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			cin >> a[i][j];
	int ans = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			ans += check(i, j);
	cout << ans << endl;
	return 0;
}