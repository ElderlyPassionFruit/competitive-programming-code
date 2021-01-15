#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
}

int ans;

void run() {
	ans = 0;
	int sum_l = 0, sum_r = 0;
	int l = 0, r = n - 1;
	while (l <= r) {
		if (sum_l + a[l] <= sum_r + a[r]) {
			sum_l += a[l];
			l++;
		}
		else {
			sum_r += a[r];
			r--;
		}
		if (sum_l == sum_r)
			ans += 2;
	}
	if (sum_l != sum_r)
		ans++;
	ans = n - ans;
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