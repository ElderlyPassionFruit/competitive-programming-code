#include <bits/stdc++.h>

using namespace std;
#define int long long
string fans;
string s, t;
void read() {
	cin >> fans >> s >> t;
}

vector <int> z_function(string s) {
	int n = s.length();
	vector <int> z(n);
	int l = 0, r = 0;
	for (int i = 1; i < n; i++) {
		if (i <= r) {
			z[i] = min(r - i + 1, z[i - l]);
		}
		while (z[i] + i < n && s[z[i]] == s[z[i] + i])
			z[i]++;
		if (r < z[i] + i - 1) {
			l = i, r = z[i] + i - 1;
		}
	}
	return z;
}

bool check(string s, string t) {
	string help = s + "@" + t;
	auto z = z_function(help);
	int n = s.size();
	for (int i = n + 1; i < help.size(); i++) {
		if (z[i] == n)
			return true;
	}
	return false;
}

int cnt(string s, string t) {
	string help = s + "@" + t;
	auto z = z_function(help);
	int n = s.size();
	int ans = 0;
	for (int i = n + 1; i < help.size(); i++) {
		ans += z[i] == n;
	}
	return ans;
}

int ans = 0;
void run() {
	string fget = "";
	vector <char> help(fans.size());
	if (!check(t, s)) {
		vector <int> dp(fans.size(), 0);
		vector <bool> pos_s(fans.size(), false);
		int n = fans.size();
		int m = s.size();
		for (int i = 0; i < n; i++) {
			if (i > 0)
				dp[i] = dp[i - 1];
			if (i - m + 1 >= 0) {
				bool flag = true;
				for (int j = 0; j < m; j++) {
					if (fans[i - m + 1 + j] == '*' || fans[i - m + 1 + j] == s[j])
						continue;
					flag = false;
					break;
				}
				if (flag){
					int num = 0;
					if (i - m >= 0)
						num = dp[i - m];
					dp[i] = max(dp[i], num + 1);
					if (num + 1 == dp[i])
						pos_s[i] = true;
				}
			}
		}
		reverse(s.begin(), s.end());
		for (int i = 0; i < n; i++) {
			if (pos_s[i] == true) {
				for (int j = 0; j < s.size(); j++)
					help[i - j] = s[j];
			}
			else {
				help[i] = fans[i];
			}
		}
		reverse(s.begin(), s.end());
	//	for (auto i : pos_s)
	//		cout << i << " ";
	//	cout << endl;
		for (auto i : help)
			fget += i;

	}
	else {
		fget = fans;
	}

	//cout << fget << " " << s << " " << t << endl;

	ans = cnt(s, fget) - cnt(t, fget);
}

void write() {
	cout << ans << endl;
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