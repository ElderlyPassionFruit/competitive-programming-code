#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e5 + 10;
int n, m;
int a[MAXN];
int cnt = 0;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

void build() {
	for (int i = 0; i < n - 1; i++) {
		if (a[i] <= a[i + 1])
			cnt++;
	}
}

vector<bool> ans;

void run() {
	build();
	for (int i = 0; i < m; i++) {
		char type;
		cin >> type;
		if (type == '?') {
			ans.push_back(cnt == n - 1);
		}
		else {
			int pos, val;
			cin >> pos >> val;
			pos--;
			if (pos - 1 >= 0) {
				if (a[pos - 1] <= a[pos]) cnt--;
				if (a[pos - 1] <= val) cnt++;
			}
			if (pos + 1 < n) {
				if (a[pos] <= a[pos + 1]) cnt--;
				if (val <= a[pos + 1]) cnt++;
			}
			a[pos] = val;
		}
	}
}

void write() {
	for (auto i : ans) {
		if (i)
			cout << "YES\n";
		else
			cout << "NO\n";
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