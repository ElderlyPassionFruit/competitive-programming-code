#include <bits/stdc++.h>

using namespace std;
#define int long long


int n;
void read() {
	cin >> n;
	if (n % 2 == 1) {
		cout << 0 << endl;
		return;
	}
	int ans = 1;
	for (int i = 0; i < n / 2; i++)
		ans *= 2;
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