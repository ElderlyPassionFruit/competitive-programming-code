#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int a;
string s;
int n;

vector<vector<int>> table;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> a;
	cin >> s;
	n = s.size();
	table.resize(n + 1, vector<int> (n + 1, 0));
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= n; j++) {
			table[i][j] = (s[i - 1] - '0') * (s[j - 1] - '0');
			table[i][j] += table[i - 1][j];
			table[i][j] += table[i][j - 1];
			table[i][j] -= table[i - 1][j - 1];
		}
	}
	ll ans = 0;
	for (int x1 = 1; x1 <= n; x1++) {
		for (int y1 = 1; y1 <= n; y1++) {
			for (int x2 = x1; x2 <= n; x2++) {
				for (int y2 = y1; y2 <= n; y2++) {
					if (table[x2][y2] - table[x1 - 1][y2] - table[x2][y1 - 1] + table[x1 - 1][y1 - 1] == a) {
						ans++;
					} 
				}
			}
		}
	}
	cout << ans << endl;
	return 0;
}