#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n, m;
	cin >> n >> m;
	vector<vector<char> > table(n, vector<char> (m, ' '));
	for (auto &i : table)
		for (auto &j : i)
			cin >> j;

	vector<int> dx = {-1, 0, 1, 0};
	vector<int> dy = {0, 1, 0, -1};
	int ed = 0;
	int v = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == '#') continue;
			v++;
			int cnt = 0;
			for (int k = 0; k < 4; k++) {
				int x = i + dx[k];
				int y = j + dy[k];
				if (x < 0 || y < 0 || x >= n || y >= m || table[x][y] == '#') continue;
				cnt++;
			}
			ed += cnt;	
			if (cnt >= 3) {
				cout << "YES" << endl;
				return 0;
			} 	
		}
	}
	ed /= 2;
	//cout << ed << endl;
	if (ed != v - 1) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
	return 0;
}