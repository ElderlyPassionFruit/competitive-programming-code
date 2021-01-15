#include <bits/stdc++.h>

using namespace std;

#define int long long

int n;
vector <int> a;

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a) {
		cin >> i;
		i--;
	}
}

string ans;

void run() {
	for (int i = 0; i < n; i++) {
		int pos = 0;
		for (int j = 0; j < n; j++) {
			if (a[j] == i) {
				pos = j;
				break;
			}
		}

		while (pos - i > 1) {
			swap(a[pos], a[pos - 1]);
			pos--;
			swap(a[pos], a[pos - 1]);
			pos--;	
		}

		if (pos == i)
			continue;
		if (pos <= n - 2) {
			swap(a[pos - 1], a[pos]);
			swap(a[pos], a[pos + 1]);
		}
	}

	vector <int> b = a;
	sort(b.begin(), b.end());
	if (a == b)
		ans = "Yes";
	else
		ans = "No";
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