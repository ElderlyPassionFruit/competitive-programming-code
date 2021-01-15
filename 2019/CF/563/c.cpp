#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
void read() {
	cin >> n;
}

vector<int> ans;
void run() {
	int num = 1;
	for (int i = 2; i <= n; i++) {
		int m = 0;
		for (int j = 2; j * j <= i; j++) {
			if (i % j == 0) {
				m = j;
				break;
			}
		}
		if (m == 0)
			ans.push_back(num++);
		else 
			ans.push_back(ans[m - 2]);
	} 
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