#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD) {
		a -= MOD;
	}
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0) {
		a += MOD;
	}
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
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
		for (; pos < n; pos |= pos + 1) {
			tree[pos] = add(tree[pos], val);
		}
	}
	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			ans = add(ans, tree[r]);
		}
		return ans;
	}
};

const int MAXN = 1e5 + 10;
int a[MAXN];
int n;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	fenwick tree(*max_element(a, a + n) + 1);
	vector<int> last(*max_element(a, a + n) + 1, 0);
	int ans = 0;
	for (int i = 0; i < n; i++) {
		int now = tree.get(a[i]);
		now = add(now, 1);
		now = mul(now, a[i]);
		now = sub(now, last[a[i]]);
		//cout << "i = " << i << " now = " << now << endl;
		ans = add(ans, now);
		last[a[i]] = add(last[a[i]], now);
		tree.upd(a[i], now);
	}
	cout << ans << endl;
	return 0;
}