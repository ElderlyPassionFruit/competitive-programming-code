#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

bool check(int a, int b, int c, int d) {
	return a == c && b == d;
}

void solve() {
	int a, b, c, d;
	cin >> a >> b >> c >> d;
	bool flag = false;
	while (true) { 
		flag |= check(a, b, c, d);
		if (b <= 0) break;
		if (b > a) swap(a, b);
		if (b == d && b > 0 && a - c > 0 && (a - c) % b == 0)
			flag = true;
		if (b > 0)
			a %= b;
	}
	if (flag) {
		cout << "YES\n";
	}
	else {
		cout << "NO\n";
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int k;
	cin >> k;
	while (k--) {
		solve();
	}
	return 0;
}