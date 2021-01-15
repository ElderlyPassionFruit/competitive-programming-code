#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct event{
	int l, r, u, v;
	event() {}
	event(int _l, int _r, int _u, int _v) {
		l = _l, r = _r, u = _u, v = _v;
	}
};

struct fquery{
	int pos, ind;
	fquery() {
	}
	fquery(int _pos, int _ind) {
		pos = _pos, ind = _ind;
	}
};

int n, q;
vector<event> have;
vector<fquery> query;

void read() {
	cin >> n >> q;
	map<pair<int, int>, int> last;
	for (int i = 0; i < q; i++) {
		char type;
		cin >> type;
		if (type == '+') {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			if (u > v) swap(u, v);
			last[{u, v}] = i;
		} else if (type == '?') {
			query.push_back({i, (int)query.size()});
		} else {
			int u, v;
			cin >> u >> v;
			u--;
			v--;
			if (u > v) swap(u, v);
			have.push_back({last[{u, v}], i + 1, u, v});
			last[{u, v}] = -1;
		}
	}
	for (auto i : last) {
		if (i.second != -1)
		have.push_back({i.second, q, i.first.first, i.first.second});
	}
}

const int MAXN = 3e5 + 10;
int par[MAXN], sz[MAXN];
vector<pair<int,int>> fdel;
int fans;

void init() {
	fans = n;
	iota(par, par + n, 0);
	fill(sz, sz + n, 1);
	fdel = {};
}

int get_par(int v) {
	if (v == par[v]) return v;
	return get_par(par[v]);
}

bool uni(int a, int b) {
	a = get_par(a);
	b = get_par(b);
	if (a == b) return false;
	if (sz[a] > sz[b]) swap(a, b);
	par[a] = b;
	sz[b] += sz[a];
	fdel.push_back({a, b});
	fans--;
	return true;
}

void del() {
	assert(!fdel.empty());
	int a = fdel.back().first;
	int b = fdel.back().second;
	sz[b] -= sz[a];
	par[a] = a;
	fans++;
	fdel.pop_back();
}

vector<int> ans;


int relax(int l, int r, vector<event> & have) {
	int ans = 0;
	vector<event> nhave;
	for (auto i : have) {
		if (i.r <= l || i.l >= r) continue;
		if (i.l <= l && r <= i.r) {
			ans += uni(i.u, i.v);
		} else {
			nhave.push_back(i);
		}
	}
	have = nhave;
	return ans;
}

void solve(int l, int r, vector<event> have, vector<fquery> q) {
	if (l >= r) return;
	int cnt = relax(l, r, have);
	if (l == r - 1) {
		for (auto i : q) {
			ans[i.ind] = fans;
		}
	}

	int m = (l + r) / 2;
	if (l != r - 1) {
		vector<fquery> ql, qr;
		for (auto i : q) {
			if (i.pos < m) {
				ql.push_back(i);
			} else {
				qr.push_back(i);
			}
		}
		solve(l, m, have, ql);
		solve(m, r, have, qr);
	}
	while (cnt--)
		del();
}

void run() {
	ans.resize(query.size());
	init();
	solve(0, q + 1, have, query);
}

void write() {
	for (auto i : ans) {
		cout << i << "\n";
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