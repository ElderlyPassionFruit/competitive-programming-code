#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

namespace Hash{
	int add(int a, int b, int mod) {
		a += b;
		if (a >= mod)
			a -= mod;
		return a;
	}

	int sub(int a, int b, int mod) {
		a -= b;
		if (a < 0)
			a += mod;
		return a;
	}

	int mul(int a, int b, int mod) {
		return (ll) a * b % mod;
	}

	const int MOD = 1e9 + 7;
	const int MAXN = 1e5 + 10;
	const int b = rnd() % 1000 + 228 + 1337;
	int pows[MAXN];
	int pref[MAXN];

	void build() {
		pows[0] = 1;
		for (int i = 1; i < MAXN; i++)
			pows[i] = mul(pows[i - 1], b, MOD);
		pref[0] = pows[0];
		for (int i = 1; i < MAXN; i++)
			pref[i] = add(pref[i - 1], pows[i], MOD);
		/*cout << "pows = " << endl;
		for (int i = 0; i < MAXN; i++)
			cout << pows[i] << " ";
		cout << endl;
		cout << "pref = " << endl;
		for (int i = 0; i < MAXN; i++)
			cout << pref[i] << " ";
		cout << endl;*/
	}	

	struct node{
		int ans, sz;
		char mod = ' ';
		node() {
			ans = sz = 0;
			mod = ' ';
		}
		node(char x) {
			ans = x;
			sz = 1;
			mod = ' ';
		}
	};

	node merge(const node & a, const node & b) {
		if (a.sz == 0) return b;
		if (b.sz == 0) return a;
		node ans;
		ans.ans = add(mul(a.ans, pows[b.sz], MOD), b.ans, MOD);
		ans.sz = a.sz + b.sz;
		ans.mod = ' ';
		return ans;
	}

	struct segment_tree{
		vector<node> tree;
		int n;

		segment_tree() {}

		void build(int v, int tl, int tr, const string & s) {
			if (tl == tr - 1) {
				tree[v] = node(s[tl]);
				return;
			}
			int tm = (tl + tr) / 2;
			build(v * 2, tl, tm, s);
			build(v * 2 + 1, tm, tr, s);
			tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
		}

		segment_tree(const string & s) {
			n = s.size();
			tree.resize(n * 4);
			build(1, 0, n, s);
			//for (int i = 0; i < n; i++)
			//	tree[i] = node(s[i]);
		}

		void push(int v) {
			if (tree[v].mod == ' ') return;
			tree[v * 2].mod = tree[v].mod;
			tree[v * 2 + 1].mod = tree[v].mod;
			tree[v].mod = ' ';
		}

		node get_val(int v) {
			if (tree[v].mod == ' ') return tree[v];
			node ans;
			ans.sz = tree[v].sz;
			ans.ans = mul(pref[ans.sz - 1], tree[v].mod, MOD);
			ans.mod = ' ';
			return ans;
		}

		node get(int v, int tl, int tr, int l, int r) {
			if (tl >= r || tr <= l) return node();
			if (tl >= l && tr <= r) return get_val(v);
			push(v);
			int tm = (tl + tr) / 2;
			node ans = merge(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
			tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
			return ans;
		}

		int get(int l, int r) {
			//node ans;
			//for (int i = l; i <= r; i++)
			//	ans = merge(ans, tree[i]);
			//return ans.ans;
			return get(1, 0, n, l, r + 1).ans;
		}

		void upd(int v, int tl, int tr, int l, int r, char x) {
			if (tl >= r || tr <= l) return;
			if (tl >= l && tr <= r) {
				tree[v].mod = x;
				return;
			} 
			push(v);
			int tm = (tl + tr) / 2;
			upd(v * 2, tl, tm, l, r, x);
			upd(v * 2 + 1, tm, tr, l, r, x);
			tree[v] = merge(get_val(v * 2), get_val(v * 2 + 1));
		}

		void upd(int l, int r, char x) {
			upd(1, 0, n, l, r + 1, x);
			//for (int i = l; i <= r; i++)
			//	tree[i] = node(x);
		}
	};

	int n;
	segment_tree norm;
	segment_tree rev;

	void init(string & s) {
		build();
		n = s.size();
		norm = segment_tree(s);
		reverse(all(s));
		rev = segment_tree(s);
	}	

	void upd(int l, int r, char x) {
		norm.upd(l, r, x);
		rev.upd(n - 1 - r, n - 1 - l, x);
	}

	bool check(int l, int r) {
		//cout << "l = " << l << " r = " << r << " get(l, r) = " << norm.get(l, r) << endl;
		//cout << "l = " << n - 1 - r << " r = " << n - 1 - l << " get(l, r) = " << rev.get(n - 1 - r, n - 1 - l) << endl;
		return norm.get(l, r) == rev.get(n - 1 - r, n - 1 - l);
	}
}

int n, q;
string s;

void read() {
	cin >> n >> q;
	cin >> s;
}

vector<bool> ans;

void run() {
	Hash::init(s);
	for (int i = 0; i < q; i++) {
		string type;
		cin >> type;
		if (type == "ask") {
			int l, r;
			cin >> l >> r;
			l--;
			r--;
			ans.push_back(Hash::check(l, r));
		}
		else if (type == "set") {
			int l, r;
			char x;
			cin >> l >> r >> x;
			l--;
			r--;
			Hash::upd(l, r, x);
		}
	}
}

void write() {
	for (auto i : ans)
		if (i)
			cout << "YES\n";
		else
			cout << "NO\n";
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