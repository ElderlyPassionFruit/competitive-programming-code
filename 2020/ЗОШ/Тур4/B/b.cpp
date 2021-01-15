#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
ll s, t;
int d;
ll sum, min_pref;
vector<ll> a;
void read() {
	cin >> s >> t >> d;
	sum = 0, min_pref = 0;
	for (int i = 0; i < d; i++) {
		ll x;
		cin >> x;
		a.push_back(x);
		sum += x;
		chkmin(min_pref, sum);
	}
	//cout << "sum = " << sum << endl;
	//cout << "min_pref = " << min_pref << endl;
	if (sum >= 0 && s + min_pref > t) {
		cout << -1 << "\n";
		exit(0);
	}
}

int need() {
	if (s + min_pref <= t) return 0;
	int l = 0, r = 1e5 + 10;
	while (l < r - 1) {
		ll mid = (l + r) / 2;
		if (s + sum * mid + min_pref <= t)
			r = mid;
		else
			l = mid;
	}
	s += sum * r;
	return r;
}

int get() {
	for (int i = 0; i < d; i++) {
		s += a[i];
		if (s <= t)
			return i + 1;
	}
	assert(false);
}

ll ans;

void run() {
	int fans = need();
	//cout << fans << " " << get() << endl;
	ans += d * fans + get();
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