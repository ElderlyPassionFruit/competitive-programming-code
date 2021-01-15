#include <bits/stdc++.h>

using namespace std;
#define int long long

struct get_min{
	int n;
	vector<int> a;
	vector<int> tree;
	get_min() {
		a = {};
		n = 0;
	}

	void build(int v, int l, int r) {
		if (l == r - 1) {
			tree[v] = a[l];
			return;
		}
		int m = (l + r) / 2;
		build(v * 2, l, m);
		build(v * 2 + 1, m, r);
		tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
	}

	get_min(vector<int> x) {
		a = x;
		n = a.size();
		tree.assign(n * 4, 1e9);
		build(1, 0, n);
	}

	int get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return 1e9;
		if (tl >= l && tr <= r)
			return tree[v];
		int tm = (tl + tr) / 2;
		return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	int get(int l, int r) {
		return get(1, 0, n, l, r + 1);
		int ans = a[l];
		for (int i = l + 1; i <= r; i++)
			ans = min(ans, a[i]);
		return ans;
	}
};

int n;
vector<int> x, y;
void read() {
	cin >> n;
	x.resize(n);
	for (auto &i : x)
		cin >> i;
	y.resize(n);
	for (auto &i : y)
		cin >> i;
}

vector <pair <int, int> > get(vector<int> a) {
	get_min help(a);
	vector<pair <int, int> > ans; 
	for (int i = 0; i < n; i++) {
		int l = i, r = n;
		while (l < r - 1) {
			int mid = (l + r) / 2;
			if (help.get(i, mid) >= a[i])
				l = mid;
			else
				r = mid;
		}

		int l2 = -1, r2 = i;
		while (l2 < r2 - 1) {
			int mid = (l2 + r2) / 2;
			if (help.get(mid, i) >= a[i])
				r2 = mid;
			else
				l2 = mid;
		}
		ans.push_back({a[i], l - r2 + 1});
	}
	return ans;
}

int get_ans(vector<pair <int, int> > a, vector<pair <int, int> > b) {
	int ans = 0;

	int can = 0;
	int pos = n;
	for (int i = n - 1; i >= 0; i--) {
		while (pos > 0 && b[pos - 1].first >= a[i].first) {
			pos--;
			can = max(can, b[pos].second);
		}
		ans = max(ans, a[i].first * a[i].second * can);
	}
	return ans;
}

int ans = 0;

void run() {
	vector<pair <int, int> > h, w;
	h = get(x);
	w = get(y);
	sort(h.begin(), h.end());
	sort(w.begin(), w.end());

	ans = max(ans, get_ans(h, w));
	ans = max(ans, get_ans(w, h));
}

void write() {
	cout << ans << endl;
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