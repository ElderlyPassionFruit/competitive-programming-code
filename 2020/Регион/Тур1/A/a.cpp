#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

ll l, r;

void read() {
	cin >> l >> r;
}

ll get(ll r) {
	ll m = 0;
	ll d = 0;
	ll h = 0;
	while (d <= r) {
		m++;
		d += m;
		h += m * (m + 1) / 2;
	}
	h -= m * (m + 1) / 2;
	d -= m;
	m--;
	for (int i = 1; i + d <= r; i++)
		h += i;
	return h;
}

ll get(ll l, ll r) {
	return get(r) - get(l - 1);
}

ll ans;

void run() {
	ans = get(l, r);
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