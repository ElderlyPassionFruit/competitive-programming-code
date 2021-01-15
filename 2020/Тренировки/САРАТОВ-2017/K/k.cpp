#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int a[10];
// 10, 20, 50, 100, 200, 500, 1 000, 2 000 и 5 000
vector<int> val = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};
vector<int> have;

void gen(int pos, int sum) {
	if (pos == 9) {
		have.push_back(sum);
		return;
	}
	for (int i = 0; i <= a[pos]; i++) {
		gen(pos + 1, sum + val[pos] * i);
	}
}

void make(int L, int R) {
	if (a[L] == 0) return;
	int x = val[R] / val[L];
	a[R] += (a[L] - x + 1) / x;
	a[L] -= (a[L] - x + 1) / x * x;
}

int mx;

void build() {
	// 10 -> 20
	make(0, 1);
	// 20 -> 100
	make(1, 3);
	// 50 -> 100
	make(2, 3);
	// 100 -> 200
	make(3, 4);
	// 200 -> 1000
	make(4, 6);
	// 500 -> 1000
	make(5, 6);
	// 1000 -> 2000
	make(6, 7);
	// 2000 -> 10000
	make(7, 9);
	// 5000 -> 10000
	make(8, 9);
	/*cout << "a = " << endl;
	for (int i = 0; i < 10; i++) {
		cout << a[i] << " ";
	}
	cout << endl;*/
	gen(0, 0);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	mx = a[9] * 10000;
	if (!have.empty()) mx += have.back();
	/*cout << "have = " << endl;
	for (auto i : have) {
		cout << i << " ";
	}
	cout << endl;*/
}

void solve() {
	int k;
	cin >> k;
	if (k > mx) {
		cout << -1 << " ";
		return;
	}
	int ans = mx;
	int cnt = k / 10000;
	for (int i = cnt - 20; i <= cnt + 20; i++) {
		if (a[9] < i || i < 0) continue;
		int pos = lower_bound(all(have), k - i * 10000) - have.begin();
		if (pos == (int)have.size()) continue;
		ans = min(ans, i * 10000 + have[pos]);
	}
	cout << ans << " ";
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	//int sum = 0;
	for (int i = 0; i < 9; i++) {
		cin >> a[i];
	//	sum += a[i] * val[i];
	}
	//cout << "sum = " << sum << endl;
	build();
	int q;
	cin >> q;
	while (q--) {
		solve();
	}
	return 0;
}