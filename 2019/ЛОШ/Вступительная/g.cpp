#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
void read() {
	cin >> n;
}
vector <int> ans;
void run() {
	for (int i = 2; i * i <= n; i++) {
		while (n % i == 0) {
			n /= i;
			ans.push_back(i);
		}
	}
	if (n != 1) {
		ans.push_back(n);
	}
	sort(ans.begin(), ans.end());
}

void write() {
	for (auto i : ans)
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