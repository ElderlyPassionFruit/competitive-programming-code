#include <bits/stdc++.h>

using namespace std;
#define int long long


int n, k;
void read() {
	cin >> n >> k;
	if (k % 2 != ((n + 1)*n / 2) % 2) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	if (k == 0) {
		int ans = n;
		for (int i = n - 1; i >= 1; i--) {
			cout << ans << " " << i << endl;
			ans = abs(ans - i);
		}
		return;
	}

	multiset <int> a;
	for (int i = 1; i <= n; i++)
		if (i != k)
			a.insert(i);
	
	while (a.size() >= 2) {
		int x = *(--a.end());
		a.erase(--a.end());
		int y = *(--a.end());
		a.erase(--a.end());
		cout << x << " " << y << endl;
		a.insert(abs(x - y));
	}
	int x = *a.begin();
	cout << x << " " << k << endl;
}

void run() {
	
}

void write() {
	
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		read();
	}
	return 0;
}	