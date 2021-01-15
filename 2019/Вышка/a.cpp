#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
map <int, int> a;
void read() {
	cin >> n >> m;
	int mx = 0, ans = 1;
	for (int i = 0; i < m; i++) {
		int x;
		cin >> x;
		a[x]++;
		if (a[x] > mx) {
			mx = a[x];
			ans = x;
		}
	}
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