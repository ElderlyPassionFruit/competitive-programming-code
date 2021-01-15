#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void INF() {
	cout << "INF\n";
	exit(0);
}

struct segm{
	int l, r;
	segm() {}
	segm(int _l, int _r) {
		l = _l, r = _r;
	}
};

bool operator<(const segm & a, const segm & b) {
	return a.l < b.l;
}

void Unique(vector<segm> & a) {
	vector<segm> ans;
	sort(all(a));
	for (auto [l, r] : a) {
		if (ans.empty() || ans.back().r < l) {
			ans.push_back({l, r});
		} else {
			chkmax(ans[ans.size() - 1].r, r);
		}
	}
	a = ans;
}

int n, m;
map<int, vector<segm>> a[2];
vector<int> coord[2];
vector<vector<segm>> na[2];

vector<vector<bool>> used;
vector<int> dx = {-1, 0, 1, 0};
vector<int> dy = {0, 1, 0, -1};
vector<int> dind = {0, 1, 0, 1};
vector<int> delta = {0, 1, 1, 0};
queue<pair<int, int>> q;

ll ans;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		int x, l, r;
		cin >> l >> r >> x;
		a[0][x].push_back({l, r});
	}

	for (int i = 0; i < m; i++) {
		int x, l, r;
		cin >> x >> l >> r;
		a[1][x].push_back({l, r});
	}

	for (int ind = 0; ind < 2; ind++) {
		for (auto &i : a[ind]) {
			Unique(i.second);
		}
	}
}

bool check(int ind, int x, int start) {
	int L = coord[ind ^ 1][start];
	int R = coord[ind ^ 1][start + 1];
	auto it = upper_bound(all(na[ind][x]), segm(L, R));
	if (it == na[ind][x].begin()) return true;
	it--;
	if (it->r >= R) return false;
	return true;
}

void add(int x, int y) {
	ans += (ll)(coord[0][x + 1] - coord[0][x]) * (coord[1][y + 1] - coord[1][y]);
}

bool check(int x, int y) {
	return x >= 0 && x < coord[0].size() - 1 && y >= 0 && y < coord[1].size() - 1;
}

void run() {
	for (int ind = 0; ind < 2; ind++) {
		for (auto i : a[ind]) {
			coord[ind].push_back(i.first);
			for (auto [l, r] : i.second) {
				coord[ind ^ 1].push_back(l);
				coord[ind ^ 1].push_back(r);
			}
		}
	}

	for (int ind = 0; ind < 2; ind++) {
		sort(all(coord[ind]));
		coord[ind].resize(unique(all(coord[ind])) - coord[ind].begin());
		if (coord[ind].empty()) INF();
		if (coord[ind][0] >= 0) INF();
		if (coord[ind].back() <= 0) INF();
	}

	for (int ind = 0; ind < 2; ind++) {
		na[ind].resize(coord[ind].size());
		for (auto i : a[ind]) {
			na[ind][lower_bound(all(coord[ind]), i.first) - coord[ind].begin()] = i.second;
		} 
	}

	used.resize(coord[0].size() - 1, vector<bool> (coord[1].size() - 1, false));

	ans = 0;
	for (int i = 0; i < coord[0].size() - 1; i++) {
		for (int j = 0; j < coord[1].size() - 1; j++) {
			if (q.empty() && coord[0][i] <= 0 && coord[0][i + 1] >= 0 && coord[1][j] <= 0 && coord[1][j + 1] >= 0) {
				q.push({i, j});
				used[i][j] = true;
			}
		}
	}

	while (!q.empty()) {
		auto v = q.front();
		add(v.first, v.second);
		q.pop();
		for (int it = 0; it < 4; it++) {
			int nx = v.first + dx[it];
			int ny = v.second + dy[it];
			bool go = check(
				dind[it],
				delta[it] + (dind[it] == 0 ? v.first : v.second),
				dind[it] == 0 ? v.second : v.first
				);
			if (!go) continue;
			if (!check(nx, ny)) INF();
			if (used[nx][ny]) continue;
			used[nx][ny] = true;
			q.push({nx, ny});
		}
	}
}

void write() {
	cout << ans << endl;
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
