#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
vector<int> a;

void read() {
	a.resize(4);
	for (auto &i : a)
		cin >> i;
}

const ld EPS = 1e-9;

ld area(ld a, ld b, ld c) {
	ld p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

ld get(ld len, vector<int> & a) {
	return area(len, a[0], a[1]) + area(len, a[2], a[3]);
}

ld solve(vector<int> a) {
	ld l = -1e9, r = 1e9;
	if (a[1] < a[0]) swap(a[1], a[0]);
	if (a[3] < a[2]) swap(a[3], a[2]);
	chkmax(l, a[1] - a[0]);
	chkmin(r, a[0] + a[1]);
	chkmax(l, a[3] - a[2]);
	chkmin(r, a[3] + a[2]);
	if (r <= l) return 0;
	//cout << a[0] << " " << a[1] << " " << a[2] << " " << a[3] << endl;
	while (abs(l - r) > EPS) {
		ld m1 = l + (r - l) / 3;
		ld m2 = r - (r - l) / 3;
		//cout << "m1 = " << m1 << " m2 = " << m2 << endl;
		if (get(m1, a) < get(m2, a))
			l = m1;
		else
			r = m2;
	}
	//cout << l << " " << r << endl;
	return get(l, a);
}

ld ans;

void run() {
	sort(all(a));
	do {
		chkmax(ans, solve(a));
	} while (next_permutation(all(a)));
}

void write() {
	cout.precision(20);
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