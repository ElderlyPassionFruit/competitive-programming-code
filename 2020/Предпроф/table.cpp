#include <bits/stdc++.h>

using namespace std;
#define all(a) a.begin(), a.end()

const int MAXN = 210;
int n;
vector<int> g[MAXN];

vector<int> order;
vector<bool> used;

void dfs(int v) {
	used[v] = true;
	for (auto i : g[v]) {
		if (used[i]) continue;
		dfs(i);
	}
	order.push_back(v);
}

signed main() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		for (int j = 0; j < i; j++) {
			if (s[j] == '+') {
				g[i].push_back(j);
			} else {
				g[j].push_back(i);
			}
		}
	}
	used.assign(n, false);
	for (int v = 0; v < n; v++) {
		if (!used[v]) {
			dfs(v);
		}
	}
	reverse(all(order));
	for (auto i : order) {
		cout << i + 1 << " ";
	}
	cout << endl;
	return 0;
}