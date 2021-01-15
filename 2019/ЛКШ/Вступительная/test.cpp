#include <bits/stdc++.h>

using namespace std;
#define int long long

int slow(int n) {
	int ans = 1;
	for (int i = 1; i <= n; i++) {
		ans *= i;
	}
	return ans;
}

int next(int now, int n, int k) {
	now *= n - k;
	now /= (k + 1);
	return now;
}

void read() {
	int n;
	cin >> n;
	int now = 1;
	cout << now << endl;
	cout << 1 << " ";
	now = next(now, n, 0);
	for (int i = 1; i < n; i++) {
		cout << now << " ";
		now = next(now, n, i);
	}
	cout << endl;
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