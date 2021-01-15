#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN = 1e5 + 10;
string s;
int n, q;

void read() {
	cin >> s >> n >> q;
}

vector<int> prefix_functin(string s) {
	int n = s.size();
	vector<int> p(n);
	for (int i = 1; i < n; i++) {
		int j = p[i - 1];
		while (j > 0 && s[i] != s[j]) {
			j = p[j - 1];
		}
		if (s[i] == s[j]) j++;
		p[i] = j;
	}
	return p;
}

const int MAXLEN = 21;
const int MAXALPH = 26;

int nxt[MAXLEN][MAXALPH];

void build() {
	string now = "";
	for (int i = 0; i <= (int)s.size(); i++) {
		for (int a = 0; a < MAXALPH; a++) {
			now += 'a' + a;
			nxt[i][a] = prefix_functin(s + "$" + now).back();
			now.pop_back();
		}
		if (i == (int)s.size()) break;
		now += s[i];
	}
}

int ncnt[MAXLEN];

struct node{
	int cnt[MAXLEN];
	string mod;

	node() {
		fill(cnt, cnt + MAXLEN, 0);
		mod = "";
	}

	node(int len) {
		fill(cnt, cnt + MAXLEN, 0);
		mod = "";
		cnt[0] = len;
	}

	void upd(string & add) {
		for (auto a : add) {
			for (int i = 0; i <= (int)s.size(); i++) {
				ncnt[nxt[i][a - 'a']] += cnt[i];
			}
			for (int i = 0; i <= (int)s.size(); i++) {
				cnt[i] = ncnt[i];
				ncnt[i] = 0;
			}
		}
		if (add.size() + mod.size() > s.size()) {
			reverse(all(mod));
			while (add.size() + mod.size() > s.size()) {
				mod.pop_back();
			}
			reverse(all(mod));
		}
		mod += add;
	}
};

node merge(const node & a, const node & b) {
	node ans;
	for (int i = 0; i <= (int)s.size(); i++) {
		ans.cnt[i] = a.cnt[i] + b.cnt[i];
	}
	return ans;
}

node tree[MAXN * 4];

void build(int v, int tl, int tr) {
	if (tl == tr - 1) {
		tree[v] = node(1);
		return;
	}
	int tm = (tl + tr) / 2;
	build(v * 2, tl, tm);
	build(v * 2 + 1, tm, tr);
	tree[v] = node(tr - tl);
}

void init() {
	build(1, 0, n);
}

void push(int v) {
	tree[v * 2].upd(tree[v].mod);
	tree[v * 2 + 1].upd(tree[v].mod);
	tree[v].mod = "";
}

void upd(int v, int tl, int tr, int l, int r, string & s) {
	if (tl >= r || tr <= l) return;
	if (tl >= l && tr <= r) {
		tree[v].upd(s);
		return;
	}
	int tm = (tl + tr) / 2;
	push(v);
	upd(v * 2, tl, tm, l, r, s);
	upd(v * 2 + 1, tm, tr, l, r, s);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void upd(int l, int r, string & s) {
	upd(1, 0, n, l, r + 1, s);
}

int get(int v, int tl, int tr, int l, int r) {
	if (tl >= r || tr <= l) return 0;
	if (tl >= l && tr <= r) return tree[v].cnt[s.size()];
	int tm = (tl + tr) / 2;
	push(v);
	int ans = get(v * 2, tl, tm, l, r) + get(v * 2 + 1, tm, tr, l, r);
	tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
	return ans;
}

int get(int l, int r) {
	return get(1, 0, n, l, r + 1);
}

void run() {
	build();
	fill(ncnt, ncnt + MAXLEN, 0);
	init();
	while (q--) {
		int t;
		cin >> t;
		if (t == 1) {
			int l, r;
			string add;
			cin >> l >> r >> add;
			l--;
			r--;
			if (add.size() > s.size()) {
				reverse(all(add));
				while (add.size() > s.size()) {
					add.pop_back();
				}
				reverse(all(add));
 			}
			upd(l, r, add);
		} else {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			cout << get(l, r) << "\n";
		}
	}
}

void write() {

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