#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector <int> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &x : a)
		cin >> x;
	reverse(a.begin(), a.end());
	int ans = 0;
	int cnt = 0;
	for (int i = 0; i < n; i++) {
		int have = a[i];
		ans += min(cnt, a[i]);
		have -= min(cnt, a[i]);
		cnt -= min(cnt, a[i]);
		cnt += have / 2;
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