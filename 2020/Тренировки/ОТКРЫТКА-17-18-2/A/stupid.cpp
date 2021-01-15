#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, q;
vector<int> a;

void read() {
	cin >> n >> q;
}

void build() {
	a.resize(2 * n);
	set<int> have, empty;
	for (int i = 1; i <= n; i++) {
		a[i * 2 - 1] = i;
		have.insert(i * 2 - 1);
	}
	for (int i = 1; i < 2 * n; i++) {
		if (!have.count(i))
			empty.insert(i);
	}
	while (!empty.empty()) {
		auto x = *(--have.end());
		have.erase(--have.end());
		auto y = *(--empty.end());
		empty.erase(--empty.end());
		a[y] = a[x];
		have.insert(y);
	}
}

ll solve() {
	int pos;
	cin >> pos;
	return a[pos];
}

vector<ll> ans;

void run() {
	build();
	cout << "a = " << endl;
	for (int i = 1; i <= n; i++)
		cout << a[i] << " ";
	cout << endl;
	exit(0);
	while (q--)
		ans.push_back(solve());
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