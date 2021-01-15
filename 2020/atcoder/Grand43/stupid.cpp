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
}

string make(string s) {
	string ans = "";
	for (int i = 0; i + 1 < s.size(); i++) {
		ans += abs(s[i] - s[i + 1]) + '0';
	}
	return ans;
} 

void run() {
	for (int i = 0; i < n - 1; i++) {
		s = make(s);
		//cout << s << endl;
	}
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