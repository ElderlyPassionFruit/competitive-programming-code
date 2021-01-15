#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 5e5 + 10;
int a[MAXN];
int n, m;

void read() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int pref[MAXN];

void build() {
	for (int i = 0; i < n - 1; i++) {
		if (a[i] >= a[i + 1])
			pref[i + 2]++;
	}
	for (int i = 1; i <= n; i++)
		pref[i] += pref[i - 1];
}

bool get(int l, int r) {
	return r != l && pref[r] == pref[l];
}

string ans = "";

void run() {
	build();
	for (int i = 0; i < m; i++) {
		int l, r;
		cin >> l >> r;
		if (get(l, r))
			ans += "Y";
		else
			ans += "N";
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