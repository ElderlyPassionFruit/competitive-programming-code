#include <bits/stdc++.h>

using namespace std;
//#define int long long

int n, m;
void read() {
	cin >> n >> m;
	if (n == 1 && m == 1) {
		cout << 1 << endl;
		exit(0);
	}
}

vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};

void dfs(int x, int y, const vector<vector<int> > & table, vector<vector<bool> > & used) {
	if (x < 0 || x >= n || y < 0 || y >= m) return;
	if (table[x][y] == 1) return;
	if (used[x][y]) return;
	used[x][y] = true;
	for (int i = 0; i < 4; i++) {
		dfs(x + dx[i], y + dy[i], table, used);
	}
}

bool check(int x, int y, const vector<vector<int> > & table, vector<vector<bool> > & used) {
	if (x < 0 || x >= n || y < 0 || y >= m) return false;
	if (table[x][y] == 1) return false;
	return used[x][y];
}

bool check(const vector<vector<int> > & table) {
	vector<vector<bool> > used(n, vector<bool> (m, false));
	//cout << "puhh" << endl;
	dfs(0, 0, table, used);
	//cout << "puhh" << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (table[i][j] == 1) {
				bool flag = false;
				for (int k = 0; k < 4; k++) {
					flag |= check(i + dx[k], j + dy[k], table, used);
				}
				if (flag == false)
					return false;
			}
		}	
	}
	return true;
}

bool check(int cnt) {
	vector<int> table(n * m);
	for (int i = 0; i < cnt; i++) {
		table[n * m - 1 - i] = 1;
	}
	do {
		vector<vector<int> > new_table(n, vector<int> (m, 0));
		for (int i = 0; i < n * m; i++)
			new_table[i / m][i % m] = table[i];
	
		if (check(new_table))
			return true;
	} while (next_permutation(table.begin(), table.end()));
	return false;
}

int ans;

void run() {
	ans = 0;
	int l = 0, r = min(29, m * n + 1);
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	ans = l;
}

void write() {
	cout << "if n == " << n << " and " << " m == " << m << ":" << endl;
	cout << "\t" << "print(" << ans << ")" << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	for (n = 7; n <= 7; n++) {
		for (m = 2; m <= 7; m++) {
			run();
			write();
		}	
	}
	return 0;
}