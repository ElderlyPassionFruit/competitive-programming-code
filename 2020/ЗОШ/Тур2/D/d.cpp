#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
const int MAXN = 4e5 + 10;
int n;
int a[MAXN];

void read() {
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

int pref[MAXN], suff[MAXN];

void build() {
	int mx = a[0], mn = a[0];
	for (int i = 0; i < n; i++) {
		chkmax(mx, a[i]);
		chkmin(mn, a[i]);
		pref[i] = mx - mn;
	}
	mx = a[n - 1], mn = a[n - 1];
	for (int i = n - 1; i >= 0; i--) {
		chkmax(mx, a[i]);
		chkmin(mn, a[i]);
		suff[i] = mx - mn;
	}
}

int ans;

void run() {
	build();
	/*cout << "a = " << endl;
	for (auto i : a)
		cout << i << " ";
	cout << endl;
	cout << "pref = " << endl;
	for (auto i : pref)
		cout << i << " ";
	cout << endl;
	cout << "suff = " << endl;
	for (auto i : suff)
		cout << i << " ";
	cout << endl;*/
	ans = 0;
	for (int i = 0; i < n - 1; i++) {
		if (max(pref[i], suff[i + 1]) < max(pref[ans], suff[ans + 1]))
			ans = i;
	}
}

void write() {
	cout << ans + 1 << "\n";
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	while (cin >> n) {
		if (n == 1) return 0;
		read();
		run();
		write();
	}
	return 0;
}