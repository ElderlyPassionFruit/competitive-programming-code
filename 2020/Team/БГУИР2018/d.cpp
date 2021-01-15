#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int INF = 1e9 + 10;
const int MAX = 1000 * 1000 * 1000;
bool check(vector<int> a) {
	int n = a.size();
	for (int i = 0; i + 1 < n; i++) {
		if (a[i] == a[i + 1])
			return false;
	}
	for (int i = 0; i < n; i++) {
		if (a[i] < 0 || a[i] > MAX)
			return false;
	}
	return true;
}

int get(vector<int> a) {
	sort(all(a));
	if (!check(a))
		return INF;
	int ans = INF;
	int l = a[0], r = a[0];
	for (int i = 0; i < a.size(); i++) {
		ans = min(ans, max(r - l, a[a.size() - 1] - a[i]));
		r = a[i];
	}
	return ans;
}

int get(string s) {
	int ans = 0;
	for (int i = 0; i < (int) s.size(); i++) {
		if (s[i] == '.') continue;
		ans *= 10;
		ans += s[i] - '0';
	}
	return ans;
}

void out(int x) {
	string ans = "";
	for (int i = 0; i < 6; i++) {
		ans += '0' + x % 10;
		x /= 10;
	}
	ans += '.';
	if (x == 0) {
		ans += '0';
	}
	else {
		while (x) {
			ans += '0' + x % 10;
			x /= 10;
		}
	}
	reverse(all(ans));
	cout << ans << endl;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	vector<int> a;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		a.push_back(get(s));
	}

	pair <int, int> ans = {1e9 + 10, 0};

	for (int i = 0; i < n; i++) {
		a.push_back(a[i] - 1);
		ans = min(ans, make_pair(get(a), a[i] - 1));
		a.pop_back();
		a.push_back(a[i] + 1);
		ans = min(ans, make_pair(get(a), a[i] + 1));
		a.pop_back();
	}

	out(ans.second);
	return 0; 
}










