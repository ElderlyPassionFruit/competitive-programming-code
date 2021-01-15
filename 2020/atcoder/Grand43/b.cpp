#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
string s;

void read() {
	cin >> n >> s;
	if (n == 1) {
		cout << s << endl;
		exit(0);
	}
	map<char, int> cnt;
	for (auto i : s) cnt[i]++;
	if (cnt.size() == 1) {
		cout << 0 << endl;
		exit(0); 
	}
	//cin >> s;
	//n = s.size();
}

string make(string s) {
	string ans = "";
	for (int i = 0; i + 1 < s.size(); i++) {
		ans += abs(s[i] - s[i + 1]) + '0';
	}
	return ans;
} 

void run() {
	while (s.size() > 1) {
		s = make(s);
		bool flag = false;
		while (s.size() > 1 && s.back() == '0') s.pop_back();
		for (int j = 0; j < s.size(); j++) {
			if (s[j] == '0') flag = true;
		}
		if (flag) break;
	}
	//cout << s << endl;
	if (s.size() == 1) return;
	int cnt0 = 0;
	int num = 0;
	for (auto i : s) chkmax(num, i - '0');
	for (auto i : s)
		cnt0 += i == '0';
	cnt0 += s.size();
	cnt0 %= 2;
	cout << cnt0 * num << endl;
	exit(0);
}

void write() {
	cout << s << endl;
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