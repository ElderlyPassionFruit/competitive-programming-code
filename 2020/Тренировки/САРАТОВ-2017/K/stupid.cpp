#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()
#define int ll
int a[10];
// 10, 20, 50, 100, 200, 500, 1 000, 2 000 и 5 000
vector<int> val = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000};
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

int mx;

void build() {
	gen(0, 0);
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
	mx = a[9] * 10000;
	if (!have.empty()) mx += have.back();
}

void solve() {
	int k;
	cin >> k;
	if (k > mx) {
		cout << -1 << " ";
		return;
	}
	int ans = *lower_bound(all(have), k);
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