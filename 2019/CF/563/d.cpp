#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, k;
void read() {
	cin >> n >> k;
}
vector<int> ans;
void run() {
	int x = 0;
	for (int i = 0; i < n; i++) {
		int a = pow(2, i);
		while ((x ^ a) == 0 || (x ^ k) == 0)
			a++;
		if (a >= pow(2, n))
			break;
		ans.push_back(a);
		x ^= a;
	}
}

void write() {
	cout << ans.size() << endl;
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