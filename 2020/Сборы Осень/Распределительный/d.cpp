#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int get(int a, int n) {
	return (n * (n - 1) / 2) * a;
}

bool check(int x, int y, int a, int b, int it) {
	int it1 = (it + 1) / 2;
	int it2 = it - it1;
	return x + get(a, it1) <= y - get(b, it2);
}

int get(int x, int y, int a, int b, int it) {
	int it1 = (it + 1) / 2;
	int it2 = it - it1;
	if (it % 2 == 1) {
		return x + get(a, it1);
	}
	else {
		return y - get(b, it2);
	}
}

int solve(int x, int y, int a, int b) {
	int l = 0, r = 2e6 + 10;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(x, y, a, b, mid))
			l = mid;
		else
			r = mid;
	}
	return get(x, y, a, b, l);
}

int stupid_solve(int x, int y, int a, int b) {
	if (x == y) {
		return x;
	}
	int it = 0;
	int cnt1 = 0, cnt2 = 0;
	while (true) {
		//cout << x << " " << cnt1 << " " << y << " " << cnt2 << endl;
		if (it % 2 == 0) {
			cnt1++;
			if (x + cnt1 * a >= y) {
				return y;
			}
			x += cnt1 * a;
		}
		else {
			cnt2++;
			if (x >= y - cnt2 * b) {
				return x;
			}
			y -= cnt2 * b;
		}
		it++;
	}
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--){
		int x, y, a, b;
		cin >> x >> y >> a >> b;
		//cout << stupid_solve(x, y, a, b) << "\n";
		cout << solve(x, y, a, b) << "\n";
	}
	return 0;
}