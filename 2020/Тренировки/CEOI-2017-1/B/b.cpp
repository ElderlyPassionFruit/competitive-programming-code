#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int Read() {
	string s;
	cin >> s;
	int ans = 0;
	int cnt = 4;
	bool flag = false;
	for (auto i : s) {
		if (i == '.') {
			flag = true;
			continue;
		}
		if (flag) cnt--;
		ans *= 10;
		ans += i - '0';
	}
	while (cnt--)
		ans *= 10;
	return ans;
}

int n;
vector<ll> a, b;

void read() {
	cin >> n;
	a.resize(n);
	b.resize(n);
	for (int i = 0; i < n; i++) {
		a[i] = Read();
		b[i] = Read();
	}
}

ll solve(vector<ll> a, vector<ll> b) {
	ll ans = 0;
	for (int i = 1; i < n; i++) {
		a[i] += a[i - 1];
		b[i] += b[i - 1];
	}
	for (int i = 0; i < n; i++) {
		ll pos = lower_bound(all(b), a[i]) - b.begin();
		if (pos == n) break;
		chkmax(ans, a[i] - (i + 1) * 10000 - (pos + 1) * 10000);
	}
	return ans;
}

ll ans;

void run() {
	sort(all(a));
	reverse(all(a));
	sort(all(b));
	reverse(all(b));
	ans = max(solve(a, b), solve(b, a));
}

string get(ll ans) {
	string fans = "";
	for (int i = 0; i < 4; i++) {
		fans += '0' + ans % 10;
		ans /= 10;
	}
	fans += ".";
	if (ans == 0) {
		fans += "0";
	}
	else {
		while (ans) {
			fans += '0' + ans % 10;
			ans /= 10;
		}
	}
	reverse(all(fans));
	return fans;
}

void write() {
	cout << get(ans) << endl;
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