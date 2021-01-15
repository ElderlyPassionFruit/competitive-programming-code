#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (x < y) x = y;}

int n, k;
vector<int> a;

void read() {
	cin >> n >> k;
	a.resize(n + k);
	for (auto &i : a)
		cin >> i;
}

void check(vector<int> & mask) {
	vector<int> ans;
	for (int i = 0; i < n + k; i++) {
		if (mask[i]) {
			ans.push_back(a[i]);
		}
	}
	for (int i = 1; i < n / 2; i++) {
		if (ans[i] + ans[n - 1 - i] != ans[i - 1] + ans[n - 1 - (i - 1)]) return;
	}
	for (auto i : ans) {
		cout << i << " ";
	}
	cout << endl;
	exit(0);
}

void run() {
	vector<int> have(n + k, 0);
	for (int i = 0; i < n; i++) {
		have[n + k - 1 - i] = 1;
	}
	do {
		check(have);
	} while (next_permutation(all(have)));
}

void write() {
	assert(false);
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0), cout.setf(ios::fixed), cout.precision(20);
    read();
    run();
    write();
    return 0;
}