#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct segment_tree{
	vector<int> tree;
	vector<int> lcp;
	vector<int> ra;
	int n;

	segment_tree(){
		tree = {};
		n = 0;
	}

	segment_tree(vector<int> a, vector<int> b) {
		tree = a;
		lcp = b;
		n = a.size();
		ra.resize(n);
		for (int i = 0; i < n; i++)
			ra[a[i]] = i;
	}

	int get_L(int pos, int min_val) {
		for (int i = pos - 1; i >= 0; i--)
			if (tree[i] >= min_val)
				return i;
		return -1;
	}

	int get_R(int pos, int min_val) {
		for (int i = pos + 1; i < n; i++)
			if (tree[i] >= min_val)
				return i;
		return -1;
	}

	int get_ans(int l, int r) {
		int ans = 1e9;
		for (int i = l; i < r; i++)
			chkmin(ans, lcp[i]);
		return ans;
	}

	bool get(int pos1, int pos2) {
		int l = get_L(ra[pos1], pos2);
		int r = get_R(ra[pos1], pos2);
		if (l == -1 && r == -1)
			return 0;
		if (l == -1 && r != -1)
			return get_ans(ra[pos1], r) >= pos2 - pos1;
		if (l != -1 && r == -1)
			return get_ans(l, ra[pos1]) >= pos2 - pos1;
		return max(get_ans(ra[pos1], r), get_ans(l, ra[pos1])) >= pos2 - pos1;
	}
};

vector<int> get(string s) {
	auto a = build_suff(s);
	auto lcp = build_lcp(s, a);
	int n = s.size();
	vector<int> ra(n);
	for (int i = 0; i < n; i++)
		ra[a[i]] = i;
	vector<int> ans(n);
	segment_tree help(a, lcp);

	for (int i = 0; i < n - 1; i++) {
		int l = i - 1, r = n;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (help.get(i, mid))
				l = mid;
			else 
				r = mid;
		}
		ans[i] = l - i;
	}
	return ans;
}

struct stupid_tree_max{
	vector<int> tree;
	vector<int> pos;
	int n;
	stupid_tree_max() {
		n = 0;
		tree = {};
	}

	void build(int v, int tl, int tr) {
		if (tl == tr - 1) {
			pos[tl] = v;
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm);
		build(v * 2 + 1, tm, tr);
	}

	stupid_tree_max(int sz) {
		n = sz;
		tree.assign(4 * n, 0);
		pos.assign(n, 0);
		build(1, 0, n);
	}

	void upd(int p, int val) {
		int v = pos[p];
		chkmax(tree[v], val);
		v /= 2;
		while (v) {
			tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
			v /= 2;
		}
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 0;
		if (tl >= l && tr <= r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int r) {
		return get(1, 0, n, 0, r);
		int ans = 0;
		for (int i = 0; i < r; i++)
			chkmax(ans, tree[i]);
		return ans;
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r);
		int ans = 0;
		for (int i = l; i < r; i++)
			chkmax(ans, tree[i]);
		return ans;
	}
}; 

struct fsum{
	vector<int> pref;
	int n;
	fsum() {
		n = 0;
		pref = {};
	}
	fsum(vector<int> arr) {
		n = arr.size();
		pref.assign(n + 1, 0);
		for (int i = 1; i <= n; i++)
			pref[i] = pref[i - 1] + arr[i - 1];
	}
	int get(int l, int r) {
		l++;
		r++;
		return pref[r] - pref[l - 1];
	}
};

vector<int> make_l(vector<int> have) {
	int n = have.size();
	stupid_tree_max help(n);
	vector<int> ans(n, -1);
	for (int i = n - 1; i >= 0; i--) {
		if (have[i] > 0)
			ans[i] = i;
		chkmax(ans[i], help.get(i));
		if (ans[i] > 0)
			ans[i] = ans[i] - i + 1;
		help.upd(i - have[i], i);
	}
	return ans;
}

void solve() {
	string s;
	cin >> s;
	cout << s << endl;
	cout << "s = " << endl;
	for (auto i : s)
		cout << i << " ";
	cout << endl;
	int n = s.size();
	auto r = get(s);

	cout << "r = " << endl;
	for (auto i : r)
		cout << i << " ";
	cout << endl;
	cout << endl;
	reverse(s.begin(), s.end());
	auto l = get(s);
	reverse(l.begin(), l.end());
	cout << "old_l = " << endl;
	for (auto i : l)
		cout << i << " ";
	cout << endl;
	l = make_l(l);
	cout << "l = " << endl;
	for (auto i : l)
		cout << i << " ";
	cout << endl;

	int ans = 0;
	fsum help(r);
	
	for (int i = 0; i < n; i++) {
		if (l[i] == 0) continue;
		int fans = help.get(i + 1, min(i + l[i], n - 1));
		if (fans == 0) continue;
		cout << "i = " << i << " fans = " << fans << endl;
		ans += fans;
	}
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	solve();
	return 0;
}




