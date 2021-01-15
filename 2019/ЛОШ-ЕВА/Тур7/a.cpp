#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
void read() {
	cin >> n;
}
int ans;
void run() {
	ans = n - min(10LL, n / 2);
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