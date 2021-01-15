#include <bits/stdc++.h>

using namespace std;
#define int long long
map <int, int> x, y;
map <pair<int, int>, int> all;
int n;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int a, b;
		cin >> a >> b;
		x[a]++;
		y[b]++;
		all[{a, b}]++;
	}
	int ans = 0;
	for (auto i : x) {
		ans += i.second * (i.second - 1) / 2;
	}
	for (auto i : y) {
		ans += i.second * (i.second - 1) / 2;
	}
	for (auto i : all) {
		ans -= i.second * (i.second - 1) / 2;
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