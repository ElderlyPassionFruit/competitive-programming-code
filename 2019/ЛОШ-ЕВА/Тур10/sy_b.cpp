#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s;
int n;
void read() {
	cin >> s;
	string help = "";
	help += s[0];
	help += s[1];
	for (int j = 2; j < s.length(); j++) {
		if (help[help.size() - 1] == help[help.size() - 2] && help[help.size() - 1] == s[j])
			continue;
		help += s[j];
	}
	s = help;
	n = s.size();
}

string get(int l, int r) {
	string ans = "";
	for (int i = l; i <= r; i++)
		ans += s[i];
	return ans;
}

int ans;
void run() {
	set<string> help;
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			help.insert(get(0, i - 1) + get(i + 1, j - 1) + get(j + 1, n - 1));
		}
	}
	/*cout << "help = " << endl;
	for (auto i : help)
		cout << i << endl;*/
	ans = help.size();
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}