#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

string s, t;

void read() {
	cin >> s >> t;
}

void run() {
	int pos1 = 0;
	while (pos1 < s.size()) {
		if (s[pos1] == t[pos1]) {
			pos1++;
		}
		else {
			break;
		}
	}
	int n = s.size();
	int pos2 = n - 1;
	while (pos2 >= 0) {
		if (s[pos2] == t[pos2]) {
			pos2--;
		}
		else {
			break;
		}
	}

	if (pos1 == n || pos2 == -1) {
		cout << "YES" << endl;
		exit(0);
	}

	string help = "";
	for (int i = pos1; i <= pos2; i++) {
		help += s[i];
	}
	string s1 = "";
	for (int i = 0; i < pos1; i++) {
		s1 += s[i];
	}
	string s2 = "";
	for (int i = pos2 + 1; i < n; i++) {
		s2 += s[i];
	}
	reverse(help.begin(), help.end());
	s = s1 + help + s2;
	if (s == t) {
		cout << "YES" << endl;
	}
	else {
		cout << "NO" << endl;
	}
}

void write() {

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