#include <bits/stdc++.h>
//Савелий, проверь задачу подалуйста. Я 3 часа жду.
using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const long long INF = 1e18 + 10;
int n;
long long l, r;
vector<pair <pair <long long, long long>, long long> > a;

void read() {
	cin >> n >> l >> r;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		long long w, c;
		cin >> w >> c;
		a[i] = {{w, c}, i};
	}
}

struct comp{
	long long w, c;
	long long fans;
	comp() {
		w = c = 0;
		fans = {};
	}
	comp(long long x, long long y, long long z) {
		w = x;
		c = y;
		fans = z;
	}
};

vector<comp> make(vector<pair <pair <long long, long long> , long long> > a) {
	vector<comp> ans;
	int n = a.size();
	for (int i = 1; i < (1 << n); i++) {
		long long sum_w = 0;
		long long sum_c = 0;
		for (int j = 0; j < n; j++) {
			if ((i >> j) & 1) {
				sum_w += a[j].first.first;
				sum_c += a[j].first.second;
			}
		}
		ans.push_back(comp(sum_w, sum_c, i));
	}
	return ans;
}

bool cmp(comp a, comp b) {
	return a.w < b.w;
}

struct get_max{
	vector<pair <long long, long long> > tree;
	int n;

	get_max() {
		n = 0;
		tree = {};
	}

	void build(int v, int tl, int tr, vector<pair <long long, long long> > & a) {
		if (tl == tr - 1) {
			tree[v] = a[tl];
			return;
		}
		int tm = (tl + tr) / 2;
		build(v * 2, tl, tm, a);
		build(v * 2 + 1, tm, tr, a);
		tree[v] = max(tree[v * 2], tree[v * 2 + 1]);
	}

	get_max(vector<pair <long long, long long> > a) {
		n = a.size();
		tree.assign(n * 4, make_pair(-INF, 0));
		build(1, 0, n, a);
	}

	pair <long long, long long> get(int v, int tl, int tr, int l, int r) {
		if (tl >= r || tr <= l)
			return make_pair(-INF, 0);
		if (tl >= l && tr <= r) 
			return tree[v];
		int tm = (tl + tr) / 2;
		return max(get(v * 2, tl, tm, l, r), get(v * 2 + 1, tm, tr, l, r));
	}

	pair <long long, long long> get(int l, int r) {
		pair <long long, long long> ans = {-INF, 0};
		if (l <= r)
			ans = get(1, 0, n, l, r + 1);
		return ans;
	}
};

long long ans, fans;

void solve(vector<comp> left, vector<comp> right) {
	vector<pair <long long, long long> > a;
	for (auto i : right) {
		a.push_back({i.c, i.fans});
	}
	get_max tree(a);

	for (auto i : left) {
		if (i.w > r) continue;
		comp x(l - i.w, 0, 0);
		int pos1 = lower_bound(right.begin(), right.end(), x, cmp) - right.begin();
		
		comp y(r - i.w, 0, 0);
		int pos2 = (--upper_bound(right.begin(), right.end(), y, cmp)) - right.begin();

		auto check = tree.get(pos1, pos2);
		if (check.first + i.c > ans) {
			ans = check.first + i.c;
			fans = check.second | i.fans;
		}
	}
}

void run() {
	vector<pair <pair <long long, long long>, long long> > first, second;
	for (int i = 0; i < n / 2; i++) {
		first.push_back(a[i]);
	}
	for (int i = n / 2; i < n; i++) {
		second.push_back(a[i]);
	}

	auto left = make(first);
	auto right = make(second);

	for (auto &i : right) {
		i.fans <<= (n / 2);
	}

	ans = 0;
	fans = 0;
	for (auto i : left) {
		if (i.w >= l && i.w <= r) {
			if (ans < i.c) {
				ans = i.c;
				fans = i.fans;
			}
		}
	}

	for (auto i : right) {
		if (i.w >= l && i.w <= r) {
			if (ans < i.c) {
				ans = i.c;
				fans = i.fans;
			}
		}	
	}

	sort(left.begin(), left.end(), cmp);
	sort(right.begin(), right.end(), cmp);
	
	solve(left, right);
	solve(right, left);
}

void write() {
	vector<int> fout;
	for (int i = 0; i < n; i++) {
		if ((fans >> i) & 1) {
			fout.push_back(i + 1);
		}
	} 
	cout << fout.size() << endl;
	for (auto i : fout) {
		cout << i << " ";
	}
	cout << endl;
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