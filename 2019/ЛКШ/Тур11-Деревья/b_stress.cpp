#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("fast-math")
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bitset>
#include <iomanip>
#include <math.h>
#include <stdlib.h>
#include <map>
#include <unordered_map>
#include <tuple>
#include <cmath>
#include <functional>
#include <cassert>
#include <algorithm>
#include <set>
#include <deque>
#include <numeric>
using namespace std;
#define kekek ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)	

struct segtree {
	int n;
	vector<int> tr;

	void build(int v, int l, int r, vector<int>& a) {
		if (l == r) {
			tr[v] = a[l];
			return;
		}

		int m = (l + r) / 2;
		build(2 * v, l, m, a);
		build(2 * v + 1, m + 1, r, a);
		tr[v] = max(tr[2 * v], tr[2 * v + 1]);
	}

	int _get(int v, int l, int r, int ql, int qr) {
		if (ql > r || l > qr) return -1e9;
		if (ql <= l && qr >= r) return tr[v];

		int m = (l + r) / 2;
		return max(_get(2 * v, l, m, ql, qr), _get(2 * v + 1, m + 1, r, ql, qr));
	}

	void _upd(int v, int l, int r, int pos, int val) {
		if (l == r) {
			tr[v] = val;
			return;
		}

		int m = (l + r) / 2;
		if (pos > m) {
			_upd(2 * v + 1, m + 1, r, pos, val);
		}
		else {
			_upd(2 * v, l, m, pos, val);
		}

		tr[v] = max(tr[2 * v], tr[2 * v + 1]);
	}

	void upd(int pos, int val) {
		_upd(1, 0, n - 1, pos, val);
	}

	int get(int l, int r) {
		return _get(1, 0, n - 1, min(l, r), max(l, r));
	}

	segtree(vector<int>& a) {
		n = a.size();
		tr.resize(4 * n);
		build(1, 0, n - 1, a);
	}
};

int max_id = -1;
vector<int> h0, h, id, par, sz, pos;
vector<vector<int>> g;
vector<vector<int>> paths;
vector<segtree> hld;

void dfs(int v, int p, int h_now) {
	h[v] = h_now;
	par[v] = p;
	sz[v] = 1;

	if (g[v].size() == 0 || (g[v].size() == 1 && p != -1)) {		// esli list
		max_id++;
		vector<int> zzz = { v };
		paths.push_back(zzz);
		id[v] = max_id;
		pos[v] = 0;
	}
	else {
		int best = 0;
		for (auto u : g[v]) {
			if (u != p) {
				dfs(u, v, h_now + 1);
				sz[v] += sz[u];
				if (sz[best] < sz[u]) {
					best = u;
				}
			}
		}

		id[v] = id[best];
		paths[id[v]].push_back(v);
		pos[v] = pos[best] + 1;
	}
}

int getmx(int i, int j) {
	if (id[i] == id[j]) {
		return hld[id[i]].get(pos[i], pos[j]);
	}

	int up_i = paths[id[i]].back(), up_j = paths[id[j]].back();
	if (h[up_i] < h[up_j]) {
		return max(getmx(par[up_i], j), hld[id[i]].get(pos[up_i], pos[i]));
	}
	else {
		return max(getmx(i, par[up_j]), hld[id[j]].get(pos[up_j], pos[j]));
	}
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	kekek;
	int n;
	cin >> n;

	h0.resize(n + 1);
	g.resize(n + 1);
	h.resize(n + 1);
	id.resize(n + 1);
	par.resize(n + 1);
	sz.resize(n + 1);
	pos.resize(n + 1);

	for (int i = 1; i <= n; i++) {
		cin >> h0[i];
	}
	for (int i = 0; i < n - 1; i++) {
		int a, b;
		cin >> a >> b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	dfs(1, -1, 0);
	for (int i = 0; i <= max_id; i++) {
		vector<int> foo;
		for (auto j : paths[i]) {
			foo.push_back(h0[j]);
		}
		segtree kek(foo);
		hld.push_back(kek);
	}

	int k;
	cin >> k;
	while (k--) {
		char zzz;
		cin >> zzz;
		if (zzz == '!') {
			int i, h;
			cin >> i >> h;
			hld[id[i]].upd(pos[i], h);
		}
		else {
			int i, j;
			cin >> i >> j;
			cout << getmx(i, j) << '\n';
		}
	}

	return 0;
}