#include <bits/stdc++.h>

using namespace std;
#define int long long
int n;
vector <pair <int, int> > a;
void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int c;
		cin >> c;
		int mn = 1e18;
		for (int j = 0; j < 2 * c; j++) {
			int x;
			cin >> x;
			if (j % 2 == 0) {
				mn = min(mn, x);
			}
		}
		a.push_back({mn, i});
	}
}

vector<int> ans;
void run() {
	ans.resize(n);
	sort(a.begin(), a.end());
	for (int i = 0; i < n; i++) {
		ans[a[i].second] = i;
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