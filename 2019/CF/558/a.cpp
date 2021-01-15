#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
void read() {
	cin >> n >> m;
	int ans;
	ans = min(max(m, 1LL), n - m);
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