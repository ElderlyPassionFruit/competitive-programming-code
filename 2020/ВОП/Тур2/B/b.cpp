#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

struct pt{
	int x, y;
	pt() {}
	pt(int _x, int _y) {
		x = _x, y = _y;
	}
};

const int MAXN = 2e5 + 10;
const int MAXLOG = 18;

int h, w, n;
pt a[MAXN];

void read() {
	cin >> h >> w >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].x >> a[i].y;
	}
}

vector<int> coord;
vector<int> have[MAXN];

int get_pos(int x) {
	int ans = lower_bound(all(coord), x) - coord.begin();
	if (ans == (int)coord.size() || coord[ans] != x) ans = -1;
	return ans;
}

vector<int> g[MAXN];
int tin[MAXN], tout[MAXN], dp[MAXN][MAXLOG], timer;
bool used[MAXN];

void dfs(int v, int p) {
	tin[v] = timer++;
	dp[v][0] = p;
	for (int i = 1; i < MAXLOG; i++)
		dp[v][i] = dp[dp[v][i - 1]][i - 1];
	for (auto i : g[v]) {
		dfs(i, v);
	}
	tout[v] = timer++;
}

bool is_upper(int v, int u) {
	return tin[v] <= tin[u] && tout[v] >= tout[u];
}

int la(int v, int len) {
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if ((1 << i) <= len) {
			v = dp[v][i];
			len -= (1 << i);
		}
	}
	return v;
}

void build() {
	for (int i = 0; i < n; i++) {
		coord.push_back(a[i].x);
	}
	sort(all(coord));
	coord.resize(unique(all(coord)) - coord.begin());
	for (int i = 0; i < n; i++) {
		have[get_pos(a[i].x)].push_back(i);
	}
	for (int i = 0; i < (int)coord.size(); i++) {
		sort(all(have[i]), [&] (int A, int B) {
			return a[A].y < a[B].y;
		});
	}

	for (int i = 0; i < n; i++) {
		int x = a[i].x;
		int nxt = get_pos(x + 1);
		if (nxt == -1) continue;
		int par = lower_bound(all(have[nxt]), i, [&] (int A, int B) {
			return a[A].y < a[B].y;
		}) - have[nxt].begin();
		if (par == (int)have[nxt].size()) continue;
		par = have[nxt][par];
		g[par].push_back(i);
		used[i] = true;
	}

	for (int i = 0; i < n; i++) {
		if (!used[i]) {
			dfs(i, i);
		}
	}
}

void solve() {
	pt s, f;
	cin >> s.x >> s.y >> f.x >> f.y;
	if (f.x < s.x) {
		cout << "No\n";
		return;
	}
	if (s.x == f.x) {
		if (s.y <= f.y) {
			cout << "Yes\n";
		} else {
			cout << "No\n";
		}
		return;
	}
	s.x = get_pos(s.x);
	if (s.x == -1) {
		cout << "No\n";
		return;
	}

	int l = -1, r = have[s.x].size();
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (a[have[s.x][mid]].y >= s.y)
			r = mid;
		else
			l = mid;
	}
	if (r == (int)have[s.x].size()) {
		cout << "No\n";
		return;
	}
	int v = have[s.x][r];
	v = la(v, f.x - coord[s.x] - 1);

	if (a[v].x != f.x - 1) {
		cout << "No\n";
		return;
	}
	if (a[v].y <= f.y) {
		cout << "Yes\n";
	} else {
		cout << "No\n";
	}
}

void run() {
	build();
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
}

void write() {

}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}

/*
2 2 2
1 1
2 1
1
1 1 2 2

*/