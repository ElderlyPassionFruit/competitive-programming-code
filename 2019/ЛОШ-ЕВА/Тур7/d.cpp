#include <bits/stdc++.h>

using namespace std;
#define int long long
int k, n, m;
set<pair <int, int> > bad;
void read() {
	cin >> k >> n >> m;
	for (int i = 0; i < n; i++) {
		int u, v;
		cin >> u >> v;
		u;
		v;
		bad.insert({u, v});
	}
}

int fans[1000];

vector<int> merge(vector<int> a, vector<int> b) {
	vector<int> ans;
	for (auto i : a) {
		for (auto j : b) {
			if (!bad.count({j, i})) {
				ans.push_back(i);
				break;
			}
		}
	}

	for (auto i : b) {
		for (auto j : a) {
			if (!bad.count({j, i})) {
				ans.push_back(i);
				break;
			}
		}
	}
	return ans;
}

void calc() {
	vector<vector<int> > table;
	for (int i = 0; i < (1 << k); i++) {
		table.push_back({i + 1});
		fans[i + 1] = 1;
	}

	k--;
	while (table.size() > 2) {
		vector<vector<int> > ftable;
		for (int i = 0; i < (1 << k); i++) {
			ftable.push_back(merge(table[i * 2], table[i * 2 + 1]));
		}
		table = ftable;
		for (int i = 0; i < (1 << k); i++) {
			for (auto j : table[i])
				fans[j]++;
		}
		k--;
	}
}

int solve(int p) {
	return fans[p];
}

vector<int> ans;

void run() {
	calc();
	for (int test = 0; test < m; test++) {
		int x;
		cin >> x;
		ans.push_back(solve(x));
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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