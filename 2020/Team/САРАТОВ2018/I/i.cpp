#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

map <string, int> s;
vector<string> a;

string get(string & s, int l, int r) {
	string ans = "";
	for (int i = l; i < r; i++)
		ans += s[i];
	return ans;
}

int getl(int pos) {
	int n = a[pos].size();
	for (int len = (n + 1) / 2; len < n; len++) {
		auto s1 = get(a[pos], 0, n - len);
		auto s2 = get(a[pos], n - len, len);
		auto s3 = get(a[pos], len, n);
		//cout << a[pos] << " " << len << " " << s1 << " " << s2 << " " << s3 << endl;
		if (s1 != s3) continue;
		if (s.count(s2)) {
			return s[s2];
		}
	}
	return -1;
}

int getr(int pos) {
	int n = a[pos].size();
	for (int len = (n + 1) / 2; len < n; len++) {
		auto s1 = get(a[pos], n - len, len);
		auto s2 = get(a[pos], len, n);
		auto s3 = get(a[pos], 0, n - len);
		if (s2 != s3) continue;
		if (s.count(s1)) {
			return s[s1];
		}
	}
	return -1;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		string x;
		cin >> x;
		s[x] = i;
		a[i] = x;
	}

	for (int i = 0; i < n; i++) {
		int pos = getl(i);
		if (pos == -1) continue;
		cout << "YES\n";
		cout << pos + 1 << " " << i + 1 << "\n";
		return 0;
	}

	for (int i = 0; i < n; i++) {
		int pos = getr(i);
		if (pos == -1) continue;
		cout << "YES\n";
		cout << i + 1 << " " << pos + 1 << "\n";
		return 0;
	}
	cout << "NO\n";
	return 0;
}