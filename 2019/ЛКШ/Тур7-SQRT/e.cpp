#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct fenvik{
	vector<int> tree;
	int n, sum;

	fenvik() {
		n = 0;
		sum = 0;
		tree = {};
	}

	fenvik(int sz) {
		n = sz + 10;
		sum = 0;
		tree.assign(n, 0);
	}

	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1)
			ans += tree[r];
		return ans;
	}

	void upd(int pos, int val) {
		sum += val;
		for (; pos < n; pos = (pos | (pos + 1)))
			tree[pos] += val;
	}

	int get_l(int r) {
		return get(r - 1);
	}

	int get_r(int l) {
		return sum - get(l);
	}
};

struct query{
	int l, r, ind;
	query() {
		l = 0, r = 0, ind = 0;
	}
	query(int a, int b, int c) {
		l = a, r = b, ind = c;
	}
};

int sq;

bool cmp(query a, query b) {
	if (a.l / sq != b.l / sq)
		return a.l < b.l;
	return a.r < b.r;
}

int n;
vector<int> a;
fenvik help;

int m;
vector<query> q;

void read() {
	cin >> n;
	help = fenvik(n);
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
		i--;
	}
	cin >> m;
	sq = max((int)sqrt(m), 1);
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		q.push_back({l, r, i});
	}
	sort(q.begin(), q.end(), cmp);
}

long long fans;

void add_l(int pos) {
	fans += help.get_l(a[pos]);
	help.upd(a[pos], 1);
} 

void add_r(int pos) {
	fans += help.get_r(a[pos]);
	help.upd(a[pos], 1);
}

void del_l(int pos) {
	fans -= help.get_l(a[pos]);
	help.upd(a[pos], -1);
}

void del_r(int pos) {
	fans -= help.get_r(a[pos]);
	help.upd(a[pos], -1);
}

long long get_ans() {
	return fans;
}

vector<long long> ans;

void run() {
	ans.resize(m);
	fans = 0;
	int l = 0, r = -1;
	for (auto test : q) {
		while (l > test.l) {
			l--;
			add_l(l);
		}
		while (r < test.r) {
			r++;
			add_r(r);
		}
		while (l < test.l) {
			del_l(l);
			l++;
		}
		while (r > test.r) {
			del_r(r);
			r--;
		}
		ans[test.ind] = get_ans();
	}
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