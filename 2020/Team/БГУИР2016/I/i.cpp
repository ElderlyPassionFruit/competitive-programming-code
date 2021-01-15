#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

string get1(int n) {
	string ans = "";
	while (n) {
		int nxt = (ans.size() % 2) + 1;
		if (n < nxt) return ans;
		n -= nxt;
		ans += '0' + nxt;
	}
	return ans;
}

string get2(int n) {
	string ans = "";
	while (n) {
		int nxt = 2 - (ans.size() % 2);
		if (n < nxt) return ans;
		n -= nxt;
		ans += '0' + nxt;
	}
	return ans;
}

int sum(string s) {
	int ans = 0;
	for (auto i : s)
		ans += i - '0';
	return ans;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	string ans1 = get1(n), ans2 = get2(n);
	if (sum(ans1) != n) ans1 = "";
	if (sum(ans2) != n) ans2 = "";
	if (ans1.size() <= ans2.size()) {
		cout << ans2 << endl;
	}
	else {
		cout << ans1 << endl;
	}
	return 0;
}










