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

event have[MAXN];
int ans[MAXN];

const int MAXZ = 1e6 + 10;
const int MAXVAL = 1500000 + 100;
vector<int> pos[MAXZ];

int Val[MAXVAL];
bool used[MAXVAL];

void build_pos() {
	for (int i = 0; i < n; i++){
		pos[a[i]].push_back(i);
	}
	for (int i = 1; i < MAXZ; i++) {
		Val[i] = Val[i - 1];
		used[i] = false;
		if (pos[i].size()) {
			used[i] = true;
			Val[i] = i;
		}
	}
}

void upd(int x) {
	if (!used[x]) return;
	Val[x] = Val[x - 1];
	used[x] = false;
	used[x + 1] = true;
}

int get_max(int x) {
	return Val[x];
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
			have[cnt] = {l, r, val, cnt};
			cnt++;
		}
	} 
	sort(have, have + cnt);
}	

void add(int x) {
	for (auto i : pos[x])
		fenvik::upd(i);
}

void solve() {
	int pos = 0;
	for (int x = 0; x < cnt; x++) {
		auto i = have[x];
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