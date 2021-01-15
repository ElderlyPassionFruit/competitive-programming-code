#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;

void read() {
	cin >> n;
}

set<vector<int>> used;

void gen(vector<int> a) {
	if (used.count(a)) return;
	used.insert(a);
	for (int i = 1; i <= (n + 1) / 2; i++) {
		vector<int> b = a;
		for (int pos = 0; pos < i; pos++) {
			swap(b[pos], b[n - i + pos]);
		}
		gen(b);
	}
}

int cnt = 0;

void run() {
	vector<int> a(n);
	iota(all(a), 0);
	gen(a);
	//a = {0, 1, 3, 2};
	gen(a);
	cout << "have = " << endl;
	sort(all(a));
	do {
		if (!used.count(a)) {
			cnt++;
			for (auto i : a) {
				cout << i << " ";
			}
			cout << endl;
		}
	} while (next_permutation(all(a)));
}

void write() {
	cout << "used = " << endl;
	for (auto i : used) {
		for (auto j : i) {
			cout << j << " ";
		}
		cout << endl;
	}
	cout << used.size() << " " << cnt << endl;
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