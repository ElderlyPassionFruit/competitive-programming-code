#include <bits/stdc++.h>

using namespace std;
#define int long long
vector <pair <int, int> > ans;
void read() {
	int n, k;
	cin >> n >> k;
	ans.push_back({n, k});
	for (int i = 0; i < k; i++) {
		int a, b;
		cin >> a >> b;
	}
}

void run() {

}

void write() {

}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		read();
		run();
		write();
	}
	cout << endl;
	for (auto i : ans)
		cout << i.first << " " << i.second << endl;
	return 0;
}