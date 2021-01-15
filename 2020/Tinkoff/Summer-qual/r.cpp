#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {
		n = 0;
		tree = {};
	}
	fenvik(int sz) {
		n = sz;
		tree.resize(n);
	}
	void upd(int pos, int val) {
		for (; pos < n; pos = (pos | (pos + 1)))
			tree[pos] += val;
	}

	int get(int pos) {
		int ans = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1)
			ans += tree[pos];
		return ans;
	}
};

struct event{
	int pos, add, ind;
};

struct query{
	int pos, l, r, ind;
};

const int MAXN = 2e5 + 10;
string s[MAXN];
int sz = 0;

int n, m;
vector<event> a;
vector<query> q;

void read() {
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int type;
		cin >> type;
		if (type == 1) {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			cin >> s[sz];
			a.push_back({l, (int)s[sz].size(), sz});
			a.push_back({r + 1, (int)s[sz].size() * (-1), sz});
			sz++;
		}
		else if (type == 2) {
			int pos, l, r;
			cin >> pos >> l >> r;
			pos--;
			int ind = q.size();
			q.push_back({pos, l, r, ind});
		}
	}
}

fenvik tree;

void upd(event a) {
	tree.upd(a.ind, a.add);
}

vector<string> ans;

int get_pos(int need) {
	int l = -1, r = m;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (tree.get(mid) >= need)
			r = mid;
		else
			l = mid;
	}
	return r;
}


void solve(query a) {
	while (a.l <= a.r) {
		int pos = get_pos(a.l);
		int cnt = tree.get(pos - 1);
		int pos_s = a.l - cnt - 1;
		while (pos_s < s[pos].size() && a.l <= a.r) {
			ans[a.ind] += s[pos][pos_s];
			pos_s++;
			a.l++;
		}
	}
}

void run() {
	sort(q.begin(), q.end(), [&] (query a, query b) {return a.pos < b.pos;});
	sort(a.begin(), a.end(), [&] (event a, event b) {return a.pos < b.pos;});
	ans.resize(q.size());
	tree = fenvik(m);
	int pos_a = 0, pos_q = 0;
	for (int i = 0; i < n; i++) {
		while (pos_a < a.size() && a[pos_a].pos == i) {
			upd(a[pos_a++]);
		}
		while (pos_q < q.size() && q[pos_q].pos == i) {
			solve(q[pos_q++]);
		}
	}
}

void write() {
	//cout << ans.size() << endl;
	for (auto i : ans)
		cout << i << "\n";
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