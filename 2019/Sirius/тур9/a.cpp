#include <bits/stdc++.h>

using namespace std;
#define int long long

int po(int x) {
	if (x == -1)
		return 0;
	return pow(2, x);
}

void read() {
	int t;
	cin >> t;
	for (int test = 0; test < t; test++) {
		int n;
		cin >> n;
		int ax = -1e9, ans1, ans2, ans3;
		for (int i = -1; i < 60; i++) {
			for (int j = i; j < 60; j++) {
				int x = po(i);
				int y = po(j);
				int n1 = n - x - y;
				if (n1 < 0)
					break;
				if (n1 % 3 != 0)
					continue;
				n1 /= 3;
				int	ax2 = ((n1 & (n1 + x)) & (n1 + y));
				if (ax2 > ax) {
					ans1 = n1;
					ans2 = n1 + x;
					ans3 = n1 + y;
					ax = ax2;
				}
			}
		}
	//	cout << endl;
		cout << ans1 << " " << ans2 << " " << ans3 << endl;
	}
}

void run() {

}

void write() {

}

signed main() {
	freopen("grants.in", "r", stdin);
	freopen("grants.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}