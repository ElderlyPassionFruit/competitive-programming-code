#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
const int MAXN = 2e5 + 10;

vector<int> d[MAXN];

void buildD() {
	for (int i = 1; i < MAXN; i++) {
		for (int j = i; j < MAXN; j += i) {
			d[j].push_back(i);
		}
	}
}

struct fenwick{
	vector<int> tree;
	int n;
	fenwick() {}
	fenwick(int _n) {
		n = _n;
		tree.assign(n, 0);
	}
	void upd(int pos, int val) {
		for (; pos < n; pos |= pos + 1)
			tree[pos] += val;
	}
	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			ans += tree[r];
		}
		return ans;
	}
	int get(int l, int r) {
		return get(r) - get(l - 1);
	}
};

int n;
int a[MAXN];
int ra[MAXN];
struct event{
	int l, ind;
	event() {}
	event(int _l, int _ind) {
		l = _l, ind = _ind;
	}
};

int q;
vector<event> have[MAXN];
int ans[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	buildD();
	cin >> n >> q;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		ra[a[i]] = i;
	}
	for (int i = 0; i < q; i++) {
		int l, r;
		cin >> l >> r;
		l--;
		r--;
		have[r].push_back({l, i});
	}
	fenwick tree(n);
	for (int r = 0; r < n; r++) {
		for (auto x : d[a[r]]) {
			if (ra[x] <= r) {
				tree.upd(ra[x], 1);
			}
		}
		for (int x = a[r] + a[r]; x <= n; x += a[r]) {
			if (ra[x] <= r) {
				tree.upd(ra[x], 1);
			}
		}
		for (auto [l, ind] : have[r]) {
			ans[ind] = tree.get(l, r);
		}
	}
	for (int i = 0; i < q; i++) {
		cout << ans[i] << "\n";
	}
	return 0;
}