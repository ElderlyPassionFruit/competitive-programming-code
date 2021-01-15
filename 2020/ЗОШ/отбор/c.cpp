#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;

#define all(x) (x).begin(), (x).end()
template <typename T1, typename T2> inline void chkmin(T1 & x, const T2 & y) {if (y < x) x = y;};
template <typename T1, typename T2> inline void chkmax(T1 & x, const T2 & y) {if (y > x) x = y;};

string s;

void read() {
	cin >> s;
}

string ans = "neither";

void run() {
	map <char, int> cnt;
	for (auto i : s)
		cnt[i]++;
	bool flag1 = true;
	bool flag2 = true;
	for (auto i : cnt) {
		flag1 &= i.second % 2 == 0;
		flag2 &= i.second % 2;
	}
	if (flag1) {
		ans = "even";
	}
	if (flag2) {
		ans = "odd";
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.setf(ios::fixed), cout.precision(20);
	read();
	run();
	write();
	return 0;
}