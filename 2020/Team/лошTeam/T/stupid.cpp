#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <string>
#include <cmath>
#include <cstdio>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <unordered_set>
#include <unordered_map>
#include <numeric>
#include <ctime> 
#include <bitset>
#include <complex>
#include <chrono>
#include <random>
#include <functional>

using namespace std;

const int INF = 1e9 + 239;

signed main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;
	vector<vector<int>> d(n, vector<int> (n, INF));
	for (int i = 0; i < n; i++) {
		d[i][i] = 0;
	}
	for (int i = 0; i < n; i++) {
		int u, v, c;
		cin >> u >> v >> c;
		u--;
		v--;
		d[u][v] = c;
		d[v][u] = c;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
			}
		}
	}
	for (int i = 0; i < n; i++) {
		int ans = 0;
		for (int j = 0; j < n; j++) {
			ans += d[i][j];
		}
		cout << ans << ' ';
	}
	cout << '\n';
}