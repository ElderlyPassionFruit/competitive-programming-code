#include <bits/stdc++.h>

using namespace std;
#define int unsigned long long
int k, n, m;
set<pair <int, int> > bad;
set<int> good;
void read() {
	cin >> k >> n >> m;
	for (int i = 0; i < n; i++) {
		int u, v;
		cin >> u >> v;
		bad.insert({u, v});
		good.insert(v);
		good.insert(u);
	}
	good.insert((1LL << 62) + 1);
}

map <int, int> fans;

pair <bool, vector<int>> merge(pair <bool, vector<int>> a, pair<bool, vector<int>> b) {
	pair <bool, vector<int> > ans;
	ans.first = a.first | b.first;
	
	if (a.first) {
		for (auto i : b.second)
			ans.second.push_back(i);
	}
	else {
		for (auto j : b.second) {	
			for (auto i : a.second) {
				if (!bad.count({i, j})) {
					ans.second.push_back(j);
					break;
				}
			}
		}
	}

	if (b.first) {
		for (auto i : a.second)
			ans.second.push_back(i);
	}
	else {
		for (auto j : a.second) {
			for (auto i : b.second) {
				if (!bad.count({i, j})) {
					ans.second.push_back(j);
					break;
				}
			}
		}
	}
	return ans;
}

pair <bool, vector<int> > calc(int tl, int tr, int level) {
	int x = *good.lower_bound(tl);
	if (x >= tr) return {true, {}};

	if (tl == tr - 1) {
		pair <bool, vector<int> > ans;
		ans.first = false;
		ans.second.push_back(tl);
		fans[tl] = level;
		return ans;
	}

	int tm = (tl + tr) / 2;
	auto l = calc(tl, tm, level - 1);
	auto r = calc(tm, tr, level - 1);
	for (auto i : l.second)
		fans[i] = level;
	for (auto i : r.second)
		fans[i] = level;

	auto ans = merge(l, r);
	return ans;
}

int solve(int x) {
	if (fans.count(x))
		return fans[x];
	else
		return k;
}
vector<int> ans;
void run() {
	calc(1, (1LL << k) + 1, k);
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