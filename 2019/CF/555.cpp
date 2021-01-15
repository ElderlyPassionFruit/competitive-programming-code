#include <bits/stdc++.h>

using namespace std;
#define int long long

void read() {
	int n;
	cin >> n;
	vector <int> a;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a.push_back(x);
	}
	int pos1 = 0, pos2 = n - 1;
	vector <char> ans;
	int mx = -1e9;
	while (ans.size() < n) {
		if (a[pos1] > mx && a[pos2] > mx)
			break;
		if (a[pos1] < a[pos2]) {
			ans.push_back('L');
			pos1++;
			mx = a[pos1 - 1];
		}
		else {
			ans.push_back('R');
			pos2--;
			mx = a[pos2 + 1];
		}
	}
	cout << ans.size() << endl;
	for (auto i : ans)
		cout << i;
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