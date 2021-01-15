#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct item{
	ll a;
	int b;
	item() {}
	item(ll _a, int _b) {
		a = _a, b = _b;
	}
};

bool operator<(const item & a, const item & b) {
	return tie(a.a, a.b) < tie(b.a, b.b);
}

int n;
vector<item> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i.a >> i.b;
	}
	sort(all(a));
}

vector<ll> pref;

void build () {
	pref.resize(n);
	for (int i = 0; i < n; i++) {
		pref[i] = a[i].b;
		if (i > 0) pref[i] += pref[i - 1];
	}
}

ll ans;

void run() {
	/*cout << "a = " << endl;
	for (auto i : a)
		cout << i.a << " " << i.b << endl;*/
	build();
	ans = 0;
	ll min_val = 0;
	for (int i = 0; i < n; i++) {
		chkmin(min_val, (i > 0 ? pref[i - 1] : 0) - a[i].a);
		chkmax(ans, pref[i] - a[i].a - min_val);
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