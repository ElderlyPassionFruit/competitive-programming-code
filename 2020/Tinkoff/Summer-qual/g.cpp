#include <bits/stdc++.h>

using namespace std;

const int MAXN = 5e3 + 10;

vector<int> gb[MAXN], gr[MAXN];
int n;

void read() {
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			char x;
			cin >> x;
			if (x == 'R') {
				gr[i].push_back(j);
			}
			else {
				gb[i].push_back(j);
			}
		}
	}
}

bool ub[MAXN];
void dfs_blue(int v) {
	ub[v] = true;
	for (auto i : gb[v]) {
		if (!ub[i]) {
			dfs_blue(i);
		}
	}
}

bool ur[MAXN];
void dfs_red(int v) {
	ur[v] = true;
	for (auto i : gr[v]) {
		if (!ur[i]) {
			dfs_red(i);
		}
	}
}

bool check(int v) {
	for (int i = 0; i < n; i++) {
		ub[i] = false;
		ur[i] = false;
	}
	dfs_blue(v);
	dfs_red(v);
	for (int i = v + 1; i < n; i++) {
		if (ub[i] && ur[i]) {
			return false;
		}
	}
	return true;
}

bool ans;

void run() {
	ans = true;
	for (int i = 0; i < n; i++) {
		ans &= check(i);
	}
}

void write() {
	if (ans) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}