#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int ll

int n, q, s, t;
vector<int> a;

void read() {
	cin >> n >> q >> s >> t;
	n++;
	a.resize(n);
	for (auto &i : a) 
		cin >> i;
}

struct fenvik{
	vector<int> tree;
	int n;
	fenvik() {}
	fenvik(int sz) {
		n = sz;
		tree.assign(n, 0);
	}

	int get(int pos) {
		int ans = 0;
		for (; pos >= 0; pos = (pos & (pos + 1)) - 1){
			ans += tree[pos];
		}
		return ans;
	}

	void upd(int pos, int val) {
		for (; pos < n; pos |= (pos + 1)){
			tree[pos] += val;
		}
	}

	void upd(int l, int r, int add) {
		upd(l, add);
		upd(r + 1, -add);
	}
};

fenvik val;

int get(int i, int j) {
	int L = a[i] + val.get(i);
	int R = a[j] + val.get(j);
	if (L < R) return 1;
	else return 0; 
}

int sum1, sum2;

void del(int i) {
	if (get(i, i + 1)) {
		sum1 -= a[i] + val.get(i) - a[i + 1] - val.get(i + 1);
	}
	else sum2 -= a[i] + val.get(i) - a[i + 1] - val.get(i + 1);
}

void add(int i) {
	if (get(i, i + 1)) {
		sum1 += a[i] + val.get(i) - a[i + 1] - val.get(i + 1);
	}
	else sum2 += a[i] + val.get(i) - a[i + 1] - val.get(i + 1);
}

void build() {
	val = fenvik(n);
	sum1 = 0, sum2 = 0;
	for (int i = 0; i + 1 < n; i++) {
		add(i);
	}
}


int solve() {
	int l, r, x;
	cin >> l >> r >> x;
	if (l > 0) del(l - 1);
	if (r + 1 < n) del(r);
	val.upd(l, r, x);
	if (l > 0) add(l - 1);
	if (r + 1 < n) add(r);
	return sum1 * s + sum2 * t;  
}

vector<int> ans;

void run() {
	build();
	while (q--) {
		ans.push_back(solve());
	}
}

void write() {
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