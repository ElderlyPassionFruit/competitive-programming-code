#include <bits/stdc++.h>

using namespace std;
#define int long long

int check(int x) {
	cout << x << endl;
	int a;
	cin >> a;
	return a;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n;
	cin >> n;
	int l = 1, r = n + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int ans = check(mid);
		if (ans == 0) {
			return 0;
		}
		if (ans == 1) {
			l = mid + 1;
		}
		if (ans == -1) {
			r = mid;
		}
	}
	check(l);
	return 0;
}