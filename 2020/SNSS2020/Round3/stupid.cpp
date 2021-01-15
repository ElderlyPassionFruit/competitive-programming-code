#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(a) (a).begin(),(a).end()

template<typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template<typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, x;

void read() {
	cin >> n >> x;
}

int ans = 0;

void upd(vector<int> now) {
	int have = 0;
	for (auto i : now) {
		have ^= i;
	}
	if (have == x) ans++;
}

void gen(vector<int> now) {
	if (now.size() == n) {
		upd(now);
		return;
	}
	if (now.empty()) {
		now.push_back(0);
	} else {
		now.push_back(now.back());
	}
	while (now.back() <= x) {
		gen(now);
		now[now.size() - 1]++;
	}
}

void run() {
	gen({});
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.precision(20), cout.setf(ios::fixed);
	read();
	run();
	write();
	return 0;
}