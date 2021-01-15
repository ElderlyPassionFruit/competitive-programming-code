#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<pair<int, int>> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) cin >> i.first >> i.second;
}

bool check(int mask) {
	for (int i = 0; i < n; i++) {
		if (!((mask >> i) & 1)) continue;
		for (int j = i + 1; j < n; j++) {
			if (!((mask >> j) & 1)) continue;
			if (a[i].first * a[j].first + a[i].second * a[j].second == 0) return false;
		}
	}
	return true;
}

int ans;

void run() {
	ans = 0;
	for (int mask = 1; mask < (1 << n); mask++) {
		ans += check(mask);
	}
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
