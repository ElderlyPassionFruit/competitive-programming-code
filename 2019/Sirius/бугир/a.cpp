#include <bits/stdc++.h>

using namespace std;
#define int long long
vector <int> a;
int n;
int sum = 0;
void read() {
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		sum += a[i];
	}
	sort(a.begin(), a.end());
}
int ans = 1e18;

void check(int x) {
	if (x >= 0 && x % 2 == 0) {
		ans = min(ans, x);
	}
}

void run() {
	for (int i = 0; i < n; i++) {
		int fans = sum - a[i];
		check(fans);
		if (a[i] == 0)
			continue;
		fans = (fans % abs(a[i]) + abs(a[i])) % abs(a[i]);
		check(fans);
		fans += abs(a[i]);
		check(fans);	
	}
}

void write() {
	if (ans == 1e18) ans = -1;
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