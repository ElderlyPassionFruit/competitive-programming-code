#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

int x, y;
void read_x() {
	string s;
	cin >> s;
	if (s[0] == '1') {
		x = 1, y = 1;
		return;
	}
	assert(s.size() > 2);
	y = 1;
	for (int i = 2; i < s.size(); i++) {
		x *= 10;
		y *= 10;
		x += s[i] - '0';	
	}
	//cout << x << " " << y << endl;
}

int n;

void read() {
	read_x();
	cin >> n;
}

bool check(int a, int b) {
	return a * y <= b * x && __gcd(a, b) == 1;
}

int ans;

void run() {
	ans = 0;
	for (int i = 2; i <= n; i++) {
		for (int j = 1; j < i; j++) {
			ans += check(j, i);
		}
	}
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