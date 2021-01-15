#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 20;
int n, k;
int g[MAXN][MAXN];

int get(int mask) {
	vector<bool> used(n, true);
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			for (int j = 0; j < n; j++) {
				used[j] = used[j] && (g[i][j] != -1);
			}
		}
	}
	int root = -1;
	/*if (root == -1) {
		cout << "mask = " << mask << endl;
		cout << "used = " << endl;
		for (int i = 0; i < n; i++) {
			cout << used[i] << " ";
		}
		cout << endl;
	}*/
	for (int i = 0; i < n; i++) {
		if (used[i]) {
			assert(root == -1);
			root = i;
		}
	}
	assert(root != -1);
	int sum = 0;
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			sum += g[root][i];
		}
	}
	return sum;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);

	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			g[i][j] = -1;
		}
	}

	/*cout << "g = " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << g[i][j] << " ";
		}
		cout << endl;
	}*/
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			cin >> g[i][j];
			g[j][i] = g[i][j];
 		}
	}
	int sum = 0;
	int cnt = 0;
	for (int mask = 0; mask < (1 << n); mask++) {
		if (__builtin_popcount(mask) == k) {
			sum += get(mask);
			cnt++;
		}
	}
	//cout << "sum = " << sum << " cnt = " << cnt << endl;
	cout << sum / cnt << endl;
	return 0;
}