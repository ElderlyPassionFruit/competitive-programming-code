#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 33;
const int MAXN = 110, MAXH = 7;
int n, k;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

struct state {
	int mask, cnt, ans;
	state() {}
	state(int _mask, int _cnt, int _ans) {
		mask = _mask, cnt = _cnt, ans = _ans;
	}
};

bool operator<(const state & a, const state & b) {
	return tie(a.mask, a.cnt, a.ans) < tie(b.mask, b.cnt, b.ans);
}

void make(vector<state> & a) {
	sort(all(a));
	vector<state> ans;
	for (auto [mask, cnt, Ans] : a) {
		if (ans.empty() || mask != ans.back().mask || cnt != ans.back().cnt) {
			ans.push_back({mask, cnt, Ans});
		} else {
			ans[ans.size() - 1].ans = add(ans[ans.size() - 1].ans, Ans);
		}
	}
	a = ans;
}

bool used[MAXN][MAXH];

vector<vector<int>> dx = {
	{0, 0, 1},
	{0, 1, 1},
	{0, 0, 1},
	{0, 1, 1}
};

vector<vector<int>> dy = {
	{0, 1, 0},
	{0, 0, 1},
	{0, 1, 1},
	{0, 0, -1}
};

void add(vector<state> & ans, const state & mask, int fmask, int dcnt) {
	if (mask.cnt + dcnt > k) return;
	if (mask.mask & fmask) return;
	ans.push_back({(mask.mask | fmask) >> 1, mask.cnt + dcnt, mask.ans});
} 

bool check(int x, int y) {
	return x >= 0 && x < n && y >= 0 && y < MAXH;
}

void calc(vector<state> & ans, const state & mask, int x, int y) {
	if (!used[x][y]) {
		add(ans, mask, 0, 0);
	}
	for (int i = 0; i < 4; i++) {
		int fmask = 0;
		bool flag = false;
		for (int j = 0; j < 3; j++) {
			if (!check(x + dx[i][j], y + dy[i][j])) {
				flag = true;
				break;
			}
			fmask |= (1 << (dx[i][j] * MAXH + dy[i][j]));
		}
		if (flag) {
			continue;
		}
		add(ans, mask, fmask, 1);
	}
}

void solve(vector<state> & mask, int x) {
	vector<state> ans;
	for (int y = 0; y < MAXH; y++) {
		for (auto i : mask) {
			if (i.mask & 1) {
				ans.push_back({i.mask >> 1, i.cnt, i.ans});
			} else {
				calc(ans, i, x, y);
			}
		}
		mask = ans;
		ans.clear();
		make(mask);
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> k;
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		int w, d;
		cin >> w >> d;
		w--;
		d--;
		used[w][d] = true;
	}

	vector<state> mask;
	mask.push_back({0, 0, 1});
	for (int i = 0; i < n; i++) {
		solve(mask, i);
	}
	int ans = 0;
	for (auto i : mask) {
		if (i.mask == 0 && i.cnt == k) {
			ans = add(ans, i.ans);
		}
	}
	cout << ans << endl;
	return 0;
}