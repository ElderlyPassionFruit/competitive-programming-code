#include <bits/stdc++.h>

using namespace std;
#define int long long

vector <int> get(string s) {
	s += 'a';
	//cout << "s = " << s << endl;
	char now = s[0];
	int cnt = 0;
	vector <int> ans(26, 0);

	for (int i = 1; i < s.length(); i++) {
		if (s[i] >= '0' && s[i] <= '9') {
			cnt = cnt * 10 + s[i] - '0';
		}
		else {
			if (cnt == 0)
				cnt = 1;
			ans[now - 'A'] += cnt;
			now = s[i];
			cnt = 0;
		}
	}
	return ans;
}


int cnt;
string s;
string type;

void read() {
	cin >> s;
	cin >> cnt;
	cin >> type;
}

int ans = 0;

void run() {
	auto v = get(s);
	for (auto &i : v)
		i *= cnt;
	auto t = get(type);
	
	/*cout << "v = ";
	for (auto i : v)
		cout << i << " ";
	cout << endl;
	cout << "t = ";
	for (auto i : t)
		cout << i << " ";
	cout << endl;
*/
	ans = 1e9 + 10;

	for (int i = 0; i < 26; i++)
		if (t[i] != 0)
			ans = min(ans, v[i] / t[i]);
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