#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, m, k;

void read() {
	cin >> n >> m >> k;
	//cout << n << " " << m << " " << k << endl;
}

int cnt_l(int x, int k) {
	//cout << "x = " << x << " k = " << k << endl;
	int need = x * (x + 1) / 2;
	if (x > k)
		need -= (x - k) * (x - k + 1) / 2;
	if (x < k)
		need += (k - x);
	return need;
}

int cnt_r(int x, int k) {
	return cnt_l(x, n - k + 1);
}

bool check(int x) {
	//cout << "x = " << x << endl;
	//cout << "cnt_l = " << cnt_l(max(1LL, x - 1), k - 1) << endl;
	//cout << "cnt_r = " << cnt_r(max(1LL, x - 1), k + 1) << endl;
	return x + cnt_l(max(1LL, x - 1), k - 1) + cnt_r(max(1LL, x - 1), k + 1) <= m;
}

int ans;

void run() {
	//cout << check(2) << endl;
	//exit(0);
	int l = 1, r = m + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	ans = l;
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