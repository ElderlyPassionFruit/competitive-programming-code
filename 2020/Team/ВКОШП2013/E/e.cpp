#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x)( x).begin(),(x).end()

map<string, set<string> > codes;

string make(string & s) {
	if (s.size() == 3)
		return s;
	else if (s.size() == 4) {
		string ans = "";
		ans += s[0];
		ans += s[1];
		ans += "-";
		ans += s[2];
		ans += s[3];
		return ans;
	}
	else if (s.size() == 5) {
		string ans = "";
		ans += s[0];
		ans += s[1];
		ans += s[2];
		ans += "-";
		ans += s[3];
		ans += s[4];
		return ans;
	}
	else if (s.size() == 6) {
		string ans = "";
		ans += s[0];
		ans += s[1];
		ans += "-";
		ans += s[2];
		ans += s[3];
		ans += "-";
		ans += s[4];
		ans += s[5];
		return ans;
	}
	else {
		string ans = "";
		ans += s[0];
		ans += s[1];
		ans += s[2];
		ans += "-";
		ans += s[3];
		ans += s[4];
		ans += "-";
		ans += s[5];
		ans += s[6];
		return ans;
	}
}

string solve(string & s) {
	string a = "";
	for (int i = 0; i < 3; i++) {
		a += s[i];
		string b = "";
		b += s[i + 1];
		b += s[i + 2];
		for (int j = i + 3; j <= i + 5; j++) {
			b += s[j];
			if (codes[a].count(b)) {
				string c = "";
				for (int k = j + 1; k < 11; k++)
					c += s[k];
				if (c[0] == '0') continue;
				return "+" + a + "(" + b + ")" + make(c);
			}
		}
	}
	return "Incorrect";
} 

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	freopen("numbers.in", "r", stdin);
	freopen("numbers.out", "w", stdout);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string c;
		int k;
		cin >> c >> k;
		for (int j = 0; j < k; j++) {
			string s;
			cin >> s;
			codes[c].insert(s);
		}
	}
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		string s;
		cin >> s;
		cout << solve(s) << "\n";
	}
	return 0;
}