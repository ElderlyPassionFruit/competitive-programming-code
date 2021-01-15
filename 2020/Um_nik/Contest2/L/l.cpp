#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e3 + 10;

int n, m;
int a[MAXN][MAXN];
bool used[MAXN][MAXN];

int have[MAXN];
int topHave;

bool check(int x) {
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < m; j++) {
			used[i][j] = false;
		}
	}
	for (int i = 0; i < n; i++) {
		topHave = 0;
		for (int j = 0; j < m; j++) {
			if (a[i][j] >= x) {
				have[topHave++] = j;
			}
		}
		for (int l = 0; l < topHave; l++) {
			for (int r = l + 1; r < topHave; r++) {
				if (used[have[l]][have[r]]) return true;
				used[have[l]][have[r]] = true;
			}
		}
	}
	return false;
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
	int l = 0, r = 1e9 + 228;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			l = mid;
		} else {
			r = mid;
		}
	}
	cout << l << endl;
	return 0;
}