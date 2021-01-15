#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % MOD;
}

int binpow(int a, int n) {
	int ans = 1;
	while (n) {
		if (n & 1) {
			ans = mul(ans, a);
		}
		a = mul(a, a);
		n >>= 1;
	}
	return ans;
}

int Div(int a, int b) {
	return mul(a, binpow(b, MOD - 2));
}

int k, n;
string s;

void read() {
	cin >> k;
	cin >> s;
	n = s.size();
}

vector<int> prefix_function (string s) {
	int n = (int) s.length();
	vector<int> pi(n);
	for (int i = 1; i < n; i++) {
		int j = pi[i - 1];
		while (j > 0 && s[i] != s[j])
			j = pi[j - 1];
		if (s[i] == s[j]) j++;
		pi[i] = j;
	}
	return pi;
}

int stupid_solve() {
	string t = s;
	for (int i = 0; i < k - 1; i++)
		t += s;
	auto fans = prefix_function(t);
	int ans = 0;
	for (auto i : fans)
		ans = add(i, ans);
	return ans;
}

int ans;

int get(int x) {
	return Div(mul(x, add(x, 1)), 2);
}

const int IT = 2;

int smart_solve() {
	string t = s;
	for (int i = 0; i < IT - 1; i++) 
		s += t;
	auto fans = prefix_function(s);
	int ans = 0;
	for (auto i : fans)
		ans = add(ans, i);

	int len = mul((int)t.size(), sub(k, IT));
	ans = add(ans, get(len + fans.back()));
	ans = sub(ans, get(fans.back()));
	return ans;
}

void run() {
	ans = 0;
	if (k <= IT)
		ans = stupid_solve();
	else
		ans = smart_solve();
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