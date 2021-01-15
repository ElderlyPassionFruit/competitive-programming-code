#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector <int> a;
void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		cin >> i;
	sort(a.begin(), a.end());
}
int ans;
void run() {
	ans = 0;
	for (int i = 0; i < n; i++) 
		if (a[i] < 0)
			ans += n - 1;
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