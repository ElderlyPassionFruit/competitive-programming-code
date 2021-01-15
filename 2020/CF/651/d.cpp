#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
	}
}

bool check(int fans) {
	int cnt = 0;
	for (auto i : a) {
		if (cnt % 2 == 0) {
			cnt++;
		} else {
			if (i <= fans) {
				cnt++;
			}
		}
	}
	if (cnt >= k) {
		return true;
	}
	cnt = 0;
	for (auto i : a) {
		if (cnt % 2 == 1) {
			cnt++;
		} else {
			if (i <= fans) {
				cnt++;
			}
		}
	}
	if (cnt >= k) {
		return true;
	}
	return false;
}

int ans;

void run() {
	int l = 0, r = 1e9 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	ans = r;
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