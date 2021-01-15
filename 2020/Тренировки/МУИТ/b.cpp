#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
set<pair<int, int>> a, ra;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.insert({x, i});
		ra.insert({i, x});
	}
}

void no() {
	cout << "NO\n";
	exit(0);
}

void run() {
	while (a.size() > 1) {
		auto have = *a.begin();
		a.erase(a.begin());
		ra.erase({have.second, have.first});
		int num = have.first;
		int pos = have.second;
		auto it = ra.lower_bound({pos, -1});
		if (it == ra.end()) it = ra.begin();
		if (it->second == num + 1) continue;
		it = ra.lower_bound({pos, -1});
		if (it == ra.begin()) it = ra.end();
		--it;
		if (it->second == num + 1) continue;
		no();
	}
}

void write() {
	cout << "YES\n";
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