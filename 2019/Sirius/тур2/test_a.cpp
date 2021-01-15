#include <bits/stdc++.h>

using namespace std;
#define int long long


int n, k;
void read() {
	cin >> n >> k;
}

void run() {
	int sum = ((n + 1) * n) / 2;
	if (sum % 2 != k % 2) {
		cout << "NO" << endl;
		return;
	}
	cout << "YES" << endl;
	vector <int> a(n);
	a[0] = k;
	if (a[0] == 0)
		a[0] = 1;
	int num = 1;
	for (int i = 1; i < n; i++) {
		if (num == k)
			num++;
		a[i] = num++;
	}
	int ans = a.back();
	for (int i = a.size() - 2; i >= 0; i--) {
		cout << a[i] << " " << ans << endl;
		ans = abs(a[i] - ans);
	}
	//if (ans != k)
	//	cout << "WA n = " << n << " x = " << k << " my_ans = " << ans << endl;
}

void write() {
	
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	/*for (int i = 1; i <= 4; i++)
		for (int j = 0; j <= i; j++) {
			k = j;
			n = i;
			run();
		}
	return 0;
	*/
cin >> t;
while (t--) {
	read();
	run();
	write();
}
	return 0;
}