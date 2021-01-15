#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES
#pragma optimizitaion_level 3
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
#include <algorithm>
#include <set>
#include <deque>
#include <numeric>
using namespace std;
#define kekek ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)	

struct node {
	int save, mx, mxy;

	node() {
		save = mx = mxy = 0;
	}
};

struct ev {
	int x, y1, y2, type;	// 0 - open, 1 - close
};

bool operator <(const ev& a, const ev& b) {
	if (a.x != b.x) return a.x < b.x;
	return a.type < b.type;
}

const int maxn = 2e4 + 5, pl = 0;
vector<node> tr;

void push(int v) {
	tr[2 * v].save += tr[v].save;
	tr[2 * v].mx += tr[v].save;
	tr[2 * v + 1].save += tr[v].save;
	tr[2 * v + 1].mx += tr[v].save;
	tr[v].save = 0;
}

void pull(int v) {
	if (tr[2 * v].mx > tr[2 * v + 1].mx) {
		tr[v].mx = tr[2 * v].mx;
		tr[v].mxy = tr[2 * v].mxy;
	}
	else {
		tr[v].mx = tr[2 * v + 1].mx;
		tr[v].mxy = tr[2 * v + 1].mxy;
	}
}

pair<int, int> getmax(int v, int l, int r, int ql, int qr) {
	if (l > qr || ql > r) return { -1, -1 };
	if (ql <= l && qr >= r) {
		return make_pair(tr[v].mx, tr[v].mxy);
	}

	int m = (l + r) / 2;
	auto f = getmax(2 * v, l, m, ql, qr), s = getmax(2 * v + 1, m + 1, r, ql, qr);

	if (f.first > s.first) {
		return f;
	}
	else return s;
}

void upd(int v, int l, int r, int ql, int qr, int d) {
	if (l > qr || ql > r) return;
	if (ql <= l && qr >= r) {
		tr[v].save += d;
		tr[v].mx += d;
		return;
	}

	push(v);
	int m = (l + r) / 2;
	upd(2 * v, l, m, ql, qr, d);
	upd(2 * v + 1, m + 1, r, ql, qr, d);
	pull(v);
}

void build(int v, int l, int r) {
	if (l == r) {
		tr[v].mxy = l;
		return;
	}
	int m = (l + r) / 2;
	build(2 * v, l, m);
	build(2 * v + 1, m + 1, r);
	pull(v);
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	kekek;

	tr.resize(4 * maxn);
	build(1, 0, maxn);
	int n;
	cin >> n;
	vector<ev> scan;
	for (int i = 0; i < n; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		x1 += pl;
		y1 += pl;
		x2 += pl;
		y2 += pl;

		scan.push_back({ x1, y1, y2, 0 });
		scan.push_back({ x2, y1, y2, 1 });
	}
	sort(scan.begin(), scan.end());

	int ans = 0, ans_x = pl, ans_y = pl;

	for (int i = 0; i < n; i++) {
		auto now = scan[i];

		if (now.type) {
			upd(1, 0, maxn, now.y1, now.y2, -1);
		}
		else {
			upd(1, 0, maxn, now.y1, now.y2, 1);
		}

		auto foo = getmax(1, 0, maxn, 0, maxn);
		if (foo.first > ans) {
			ans = foo.first;
			ans_x = now.x;
			ans_y = foo.second;
		}
	}

	cout << ans << '\n' << ans_x - pl << " " << ans_y - pl << '\n';

	//system("pause");
	return 0;
}
