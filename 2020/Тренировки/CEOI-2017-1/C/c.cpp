#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct stage{
	vector<int> used;
	int now, type;
	stage() {}
	stage(int _now, int _type, vector<int> _used) {
		now = _now, type = _type, used = _used;
	}
};

bool operator<(const stage & a, const stage & b) {
	return tie(a.now, a.used, a.type) < tie(b.now, b.used, b.type);
}
const int MAXN = 15;
vector<pair<int, int>> g[MAXN];
int n, t, m;

void read() {
	cin >> n >> t >> m;
	t--;
	m--;
	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;
		u--;
		v--;
		g[u].push_back({v, i});
		g[v].push_back({u, i});
	}
}

map<stage, int> have;

void solve(stage a, int it) {
	//cout << it << " ";
	//cout << endl;
	if (have.count(a)) {
		if (a.type == 0) {
			if (have[a] <= it) return;
		}
		else {
			if (have[a] >= it) return;
		}
	}
	have[a] = it;
	if (a.type == 0) {
		solve({a.now, 1, a.used}, it);
		for (int i = 0; i < n - 1; i++) {
			if (a.used[i] == 0) {
				a.used[i] = 2;
				solve(a, it + 1);
				a.used[i] = 0;
			}
			else if (a.used[i] == 1) {
				a.used[i] = 0;
				solve(a, it + 1);
				a.used[i] = 1;
			}
		}
	}
	else {
		bool flag = false;
		int v = a.now;
		for (auto [to, ind] : g[a.now]) {
			if (a.used[ind] != 0) continue;
			a.now = to;
			a.used[ind] = 1;
			solve(a, it);
			a.now = v;
			flag = true;
			a.used[ind] = 0;
		}
		if (!flag) solve({a.now, 0, a.used}, it);
	}
}

void run() {
	solve(stage(m, 0, vector<int> (n - 1, 0)), 0);
	cout << "have = " << endl;
	for (auto i : have) {
		cout << "now = " << i.first.now << " flag = " << i.first.type << " ";
		cout << "used = ";
		for (auto j : i.first.used)
			cout << j << " ";
		cout << " ans = " << i.second << endl; 
 	}
}

void write() {
	int ans = 1e9;
	for (auto i : have) {
		if (i.first.now == t) {
			chkmin(ans, i.second);
		}
	}
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


/*
10 1 4
1 2
2 3
2 4
3 9
3 5
4 7
4 6
6 8
7 10
*/