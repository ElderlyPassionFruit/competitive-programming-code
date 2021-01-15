#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

#define int ll

void no() {
	cout << 2 << endl;
	exit(0);
}

void yes(int x) {
	cout << 1 << endl << x << endl;
	exit(0);
}

int x;
vector<int> a;

void read() {
	cin >> x;
	for (int i = 2; i * i <= x; i++) {
		if (x % i == 0) {
			a.push_back(i);
			a.push_back(x / i);
		}
	}
	sort(all(a));
	a.resize(unique(all(a)) - a.begin());
	if (a.empty()) {
		cout << "1\n0\n";
		exit(0);
	}
	a.push_back(x);
}

vector<int> dp;

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	read();
	int n = a.size();
	dp.assign(n, 0);
	for (int i = 0; i < n; i++) {
		bool ok = false;
		int cnt = 0;
		for (int j = 0; j < i; j++) {
			if (a[i] % a[j] != 0) continue;
			cnt++;
			if (!dp[j]) {
				ok = true;
				break;
			}
		}
		if (!cnt || ok) {
			dp[i] = 1;
		} else {
			dp[i] = 0;
		}
	}
	/*cout << "a = " << endl;
	for (auto i : a) {
		cout << i << " ";
	}
	cout << endl;
	cout << "dp = " << endl;
	for (auto i : dp) {
		cout << i << " ";
	}
	cout << endl;*/
	if (!dp[n - 1]) no();
	for (int i = 0; i < n - 1; i++) {
		if (a[n - 1] % a[i]) continue;
		if (dp[i]) continue;
		yes(a[i]);
	}
	assert(false);
	return 0;
}