#include <bits/stdc++.h>

using namespace std;
#define int long long

int check(int last, int a, int b) {
	if (a > b)
		swap(a, b);
	if (a == 2 && b == 3)
		return -1;
	if (last == 3 && a == 1 && b == 2)
		return 2;
	if (a == 1 && b == 2)
		return 3;
	if (a == 1 && b == 3)
		return 4;
	return 0;
}

void read() {
	int n;
	cin >> n;
	int last = -1;
	int t;
	cin >> t;
	int ans = 0;
	for (int i = 0; i < n - 1; i++) {
		int x;
		cin >> x;
		if (check(last, x, t) == -1) {
			cout << "Infinite" << endl;
			return;
		}
		ans += check(last, x, t);
		last = t;
		t = x;
	}
	cout << "Finite" << endl;
	cout << ans << endl;
}

void run() {

}

void write() {

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