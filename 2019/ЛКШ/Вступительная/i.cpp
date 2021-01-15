#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
const int MAXN = 3 * 1e5 + 10;
int a[MAXN], b[MAXN];
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	for (int i = 0; i < n; i++) {
		cin >> b[i];
	}
}

int f(int x) {
	int ans = 0;
	int cnt = 0;
	for (int i = n / 2; i < n; i++) {
		ans += abs(a[i] - (x + cnt));
		ans += abs(b[i] - (x + cnt));
		cnt++;
	}
	cnt = 1;
	for (int i = n / 2 - 1; i >= 0; i--) {
		ans += abs(a[i] - (x + cnt));
		ans += abs(b[i] - (x + cnt));
		cnt++;
	}
	return ans;
}
int ans;
void run() {
	int l = 0, r = 1e12 + 10;
	while (l < r - 2) {
		int mid1 = l + (r - l) / 3;
		int mid2 = r - (r - l) / 3;
		if (f(mid1) > f(mid2)) {
			l = mid1;
		}
		else {
			r = mid2;
		}
	}
	ans = 1e18;
	for (int i = l; i <= r; i++)
		ans = min(ans, f(i));
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