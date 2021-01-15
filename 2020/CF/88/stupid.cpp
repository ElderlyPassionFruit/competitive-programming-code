#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k;

void read() {
	cin >> n >> k;
	swap(n, k);
}

int calc(int x, vector<int> & have) {
	for (auto i : have) {
		x %= i;
	}
	return x;
}

set<vector<int>> ans;

void check(vector<int> have) {
	for (int i = 0; i < 100; i++) {
		int ans = calc(i, have);
		do {
			if (calc(i, have) != ans) return;
		} while (next_permutation(all(have)));
	}
	ans.insert(have);
}

void gen(vector<int> have) {
	if (have.size() == n) {
		check(have);
		return;
	}
	if (have.empty()) have.push_back(1);
	else have.push_back(have.back() + 1);
	while (have.back() <= k) {
		gen(have);
		have[have.size() - 1]++;
	}
}

void run() {
	gen({});
}

void write() {
	cout << ans.size() << endl;
	for (auto i : ans) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
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