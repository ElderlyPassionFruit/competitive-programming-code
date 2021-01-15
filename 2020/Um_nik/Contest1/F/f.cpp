#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

int n, k;

int calcDeg(int root, vector<vector<int>> & g) {
	int ans = 0;
	for (int i = 0; i < n; i++) {
		ans += g[root][i] != -1;
	}
	return ans;
}

void solveK2() {
	vector<vector<int>> g(n, vector<int> (n, -1));
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			cin >> g[i][j];
			g[j][i] = g[i][j];
		}
	}
	int root = 0;
	for (int i = 1; i < n; i++) {
		if (calcDeg(i, g) > calcDeg(root, g)) {
			root = i;
		}
	}
	assert(calcDeg(root, g) == n - 1);
	int sum2 = 0, sumN = 0;
	for (int i = 0; i < n; i++) {
		if (i == root) continue;
		for (int j = i + 1; j < n; j++) {
			if (g[i][j] != -1 && j != root) {
				//cout << "i = " << i << " j = " << j << endl;
				sum2 += g[i][j];
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (i == root) continue;
		sumN += g[root][i];
	}
	//cout << "sum2 = " << sum2 << " sumN = " << sumN << endl; 
	cout << (sum2 * 2 + sumN * (n - 1)) / ((n * (n - 1)) / 2) << endl;
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	if (k == 2) {
		solveK2();
	}
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			int x;
			cin >> x;
			if (k > 1) {
				assert(x != -1);
			}
			x = max(x, 0LL);
			sum += x;
		}
	}
	cout << 2 * sum / n << endl;
	return 0;
}