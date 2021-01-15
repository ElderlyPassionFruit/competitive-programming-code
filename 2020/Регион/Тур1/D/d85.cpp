#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,sse4.1,sse4.2,avx,avx2,mmx,abm")
#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

namespace fenvik{
	const int MAXN =  1e6 + 10;
	int tree[MAXN];
	int n = MAXN;

	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ans += tree[r];
		return ans;
	}

	int get(int l, int r) {
		return get(r) - get(l - 1);
	}

	void upd(int pos) {
		for (; pos < n; pos |= pos + 1)
			tree[pos]++;
	}
};

const int MAXN = 5e5 + 10;

int n, q;
int a[MAXN];
int mx_val = 0;
void read() {
	scanf("%d%d", &n, &q);
	for (int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		chkmax(mx_val, a[i]);
	}
}

struct event{
	int l, r, val, ind;
	event() {}
	event(int a, int b, int c, int d) {
		l = a, r = b, val = c, ind = d;
	}
};

bool operator<(const event & a, const event & b) {
	return a.val < b.val;
}

vector<event> have;
int ans[MAXN];

const int MAXZ = 1e6 + 10;

vector<int> pos[MAXZ];

struct fset{
	int pos, val;
	fset() {}
	fset(int a, int b) {
		pos = a, val = b;
	}
};

bool operator<(const fset & a, const fset & b) {
	return a.pos < b.pos;
}

set<fset> help;

const int MAXVAL

void build_pos() {
	for (int i = 0; i < n; i++){
		help.insert({a[i], a[i]});
		pos[a[i]].push_back(i);
	}
}

void upd(int x) {
	auto it = help.lower_bound({x, x});
	if (it == help.end()) return;
	if (it->pos != x) return;
	auto it2 = help.lower_bound({x + 1, x + 1});
	if (it2 != help.end() && it2->pos == x + 1) {
		help.erase(it);
		return;
	}
	else {
		help.insert({it->pos + 1, it->val});
		help.erase(it);
	}
}

int get_max(int x) {
	auto it = help.upper_bound({x, x});
	if (it == help.begin()) return 0;
	--it;
	return it->val;
}

int cnt = 0;

void build() {
	build_pos();
	for (int test = 0; test < q; test++) {
		int type;
		scanf("%d", &type);
		if (type == 1) {
			int x;
			scanf("%d", &x);
			upd(x);
		}
		else {
			int l, r, val;
			scanf("%d%d%d", &l, &r, &val);
			l--;
			r--;
			val = get_max(val);		
			have.push_back({l, r, val, cnt++});
		}
	} 
	sort(all(have));
}	

void add(int x) {
	for (auto i : pos[x])
		fenvik::upd(i);
}

void solve() {
	int pos = 0;
	for (auto i : have) {
		while (pos < i.val) {
			pos++;
			add(pos);
		}
		ans[i.ind] = fenvik::get(i.l, i.r);
	}
}

void run() {
	build();
	solve();
}

void write() {
	for (int i = 0; i < cnt; i++)
		printf("%d\n", ans[i]);
}

signed main() {
	read();
	run();
	write();
	return 0;
}