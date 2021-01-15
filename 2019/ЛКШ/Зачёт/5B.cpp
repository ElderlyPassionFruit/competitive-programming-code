#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct rect{
	int x1, y1, x2, y2;
};

const int INF = 1e9 + 10;

namespace fget{
	struct segment_tree{
		vector<int> tree, pos;
		int n;

		segment_tree() {
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

		segment_tree(int sz) {
			n = sz;
			tree.assign(n * 4, -1);
			pos.resize(n);
			build(1, 0, n);
		}

		int get(int v, int tl, int tr, int l, int r) {
			if (tl >= r || tr <= l)
				return INF;
			if (tl >= l && tr <= r)
				return tree[v];
			int tm = (tl + tr) / 2;
			return min(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
		}

		int get(int l, int r) {
			return get(1, 0, n, l, r + 1);
		}

		void upd(int p, int val) {
			int v = pos[p];
			tree[v] = val;
			v /= 2;
			while (v) {
				tree[v] = min(tree[v * 2], tree[v * 2 + 1]);
				v /= 2;
			}
		}
	};

	vector<pair <int, int> > pt;
	int n, m;

	void make(int n1, int m1, vector<pair <int, int> > a) {
		n = n1;
		m = m1;
		pt = a; 
	}

	vector<bool> solve(const vector<pair <rect, int> > & query, const vector<vector<int> > & pt) {
		segment_tree help(max(n, m));
		int q = query.size();
		vector<bool> ans(q);
		int pos = 0;

		for (int i = 0; i < max(n, m); i++) {
			for (auto j : pt[i]) {
				help.upd(j, i);
			}

			while (pos < q && query[pos].first.x2 == i) {
				int fans = help.get(query[pos].first.y1, query[pos].first.y2);
				if (fans >= query[pos].first.x1)
					ans[query[pos].second] = 1;
				pos++;
			}
		}
		return ans;
	}

	bool cmp(pair <rect, int> & a, pair <rect, int> & b) {
		return a.first.x2 < b.first.x2;
	}

	vector<bool> get(vector<pair <rect, int> > & query) {
		int q = query.size(); 
		vector<bool> ans(q);
		vector<pair <rect, int> > q2;
		for (auto i : query) {
			q2.push_back({{i.first.y1, i.first.x1, i.first.y2, i.first.x2}, i.second});
		}

		sort(query.begin(), query.end(), cmp);
		sort(q2.begin(), q2.end(), cmp);

		vector<vector<int> > pt1(max(n, m));
		for (auto i : pt) {
			pt1[i.first].push_back(i.second);
		}

		auto ans1 = solve(query, pt1);

		vector<vector<int> > pt2(max(n, m));
		for (auto i : pt) {
			pt2[i.second].push_back(i.first);
		}

		auto ans2 = solve(q2, pt2);

		for (int i = 0; i < q; i++) 
			ans[i] = (ans1[i] || ans2[i]);
		return ans;
	}
}

int n, m, k, q;
vector<pair <int, int> > a;

void read() {
	cin >> n >> m >> k >> q;
	a.resize(k);
	for (auto &i : a) {
		cin >> i.first >> i.second;
		i.first--;
		i.second--;
	}
}

vector<bool> ans;

void run() {
	fget::make(n, m, a);
	vector<pair <rect, int> > query;
	for (int i = 0; i < q; i++) {
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;
		x1--;
		y1--;
		x2--;
		y2--;
		query.push_back({{x1, y1, x2, y2}, i});
	}
	ans = fget::get(query);
}

void write() {
	for (auto i : ans) {
		if (i)
			cout << "YES\n";
		else
			cout << "NO\n";
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