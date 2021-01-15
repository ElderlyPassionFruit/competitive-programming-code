#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 200;
int n, q;
int a[MAXN];

void read() {
	cin >> n >> q;
	for (int i = 0; i < n; i++)
		cin >> a[i];
}

void add(int x) {
	for (int i = 0; i < n; i++)
		if (a[i] == x)
			a[i]++;
}

int get(int l, int r, int x) {
	int ans = 0;
	for (int i = l; i <= r; i++)
		ans += a[i] <= x;
	return ans;
}

void run() {
	for (int i = 0; i < q; i++) {
		int t;
		cin >> t;
		if (t == 1) {
			int x;
			cin >> x;
			add(x);
		}
		else {
			int l, r, val;
			cin >> l >> r >> val;
			cout << get(l - 1, r - 1, val) << endl;
		}
	}
}

void write() {

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