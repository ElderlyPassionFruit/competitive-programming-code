#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

int getPos(string s) {
	int ans = 0;
	for (auto i : s) {
		ans++;
		if (i == '.') break;
	}
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<string> s(n);
	int mx = 0;
	for (auto &i : s) {
		cin >> i;
		mx = max(mx, getPos(i));
	}
	for (auto i : s) {
		int x = getPos(i);
		x = mx - x;
		while (x--) cout << "#";
		cout << i << "\n";
	}
	return 0;
}