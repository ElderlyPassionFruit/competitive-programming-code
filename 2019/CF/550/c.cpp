#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
set <int> b;
map <int, int> a;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x]++;
	}
}

vector <int> ans1, ans2;
void run() {
	for (auto i : a) {
		if (i.second > 2) {
			cout << "NO" << endl;
			exit(0);
		}
		if (i.second == 2) {
			ans1.push_back(i.first);
			ans2.push_back(i.first);
		}
		else {
			ans1.push_back(i.first);
		}
	}
}

void write() {
	reverse(ans2.begin(), ans2.end());
	cout << "YES" << endl;
	cout << ans1.size() << endl;
	for (auto i : ans1)
		cout << i << " ";
	cout << endl;
	cout << ans2.size() << endl;
	for (auto i : ans2)
		cout << i << " ";
	cout << endl;

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