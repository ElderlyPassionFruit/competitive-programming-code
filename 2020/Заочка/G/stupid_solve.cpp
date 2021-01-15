#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> a;
int b;

int read_int() {
	string s;
	cin >> s;
	int ans = 0;
	for (auto i : s) {
		ans *= 2;
		ans += i - '0';
	}
	return ans;
}

void read() {
	cin >> n;
	a.resize(n);
	for (auto &i : a)
		i = read_int();
	b = read_int();
}

bool check(int x) {
	int ans = b;
	for (int i = 0; i < n; i++)
		ans ^= (a[i] + x);
	return ans == 0;
}

string write_int(int i) {
	string ans = "";
	if (i == 0)
		return "0";
	while (i) {
		ans += '0' + i % 2;
		i /= 2;
	}
	reverse(all(ans));
	return ans;
}

string ans;

void run() {
	ans = "-1";
	for (int i = 0; i < (1 << 13); i++) {
		if (check(i)) {
			ans = write_int(i);
			return;
		}
	}
}

void write() {
	cout << ans;
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