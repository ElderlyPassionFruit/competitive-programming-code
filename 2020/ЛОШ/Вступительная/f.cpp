#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void no() {
	cout << "impossible" << endl;
	exit(0);
}

int n;
multiset<int> a;

void read() {
	cin >> n;
	for (int i = 0; i < (1 << n); i++) {
		int x;
		cin >> x;
		a.insert(x);
	}
	if (a.find(0) == a.end()) no();
	a.erase(a.find(0));
}

vector<int> ans;

int get(int mask) {
	return __builtin_popcount(mask);
}

void run() {
	ans.resize(n, -1);
	for (int mask = 1; mask < (1 << n); mask++) {
		ll sum = 0;
		int pos = 0;
		for (int i = n - 1; i >= 0; i--) {
			if ((mask >> i) & 1) {
				pos = i;
				sum += ans[i];
			}
		}
		if (get(mask) == 1) {
			int x = *a.begin();
			a.erase(a.begin());
			ans[pos] = x;
		} else {
			auto it = a.find(sum);
			if (it == a.end()) {
				no();
			}
			a.erase(it);
		}
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