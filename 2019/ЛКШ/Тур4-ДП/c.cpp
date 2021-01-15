#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int base = 10;

typedef vector<int> lnum;
typedef vector<vector<int> > matrix;

lnum n;
int m, mod;

lnum read(string s) {
	int n = s.size();
	lnum ans(n);
	for (int i = 0; i < n; i++) {
		ans[i] = s[n - 1 - i] - '0';
	}
	return ans;
}

lnum Minus_1(lnum x) {
	int n = x.size();
	for (int i = 0; i < n; i++) {
		if (x[i] > 0) {
			x[i]--;
			break;
		}
		x[i] = 9;
	}
	while (!x.empty() && x.back() == 0) {
		x.pop_back();
	}
	return x;
}

lnum Div_2(lnum x) {
	int n = x.size();
	for (int i = n - 1; i >= 0; i--) {
		if (x[i] % 2) {
			x[i - 1] += 10;
		}
		x[i] /= 2;
	}
	while (!x.empty() && x.back() == 0) {
		x.pop_back();
	}
	return x;
}

bool is_zero(lnum x) {
	for (auto i : x)
		if (i != 0)
			return false;
	return true;
}

matrix mul(matrix a, matrix b) {
	int n = a.size();
	int m = b.size();
	int k = b[0].size();
	matrix c(n, vector<int> (k, 0));
	for (int t = 0; t < m; t++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < k; j++) {
				c[i][j] += (long long) a[i][t] * b[t][j] % mod;
				c[i][j] %= mod;
			}
		}
	}
	return c;
}

matrix fastpow(matrix a, lnum n) {
	if (is_zero(n)) {
		matrix ans(a.size(), vector<int> (a.size(), 0));
		for (int i = 0; i < a.size(); i++)
			ans[i][i] = 1;
		return ans;
	}
	if (n[0] % 2) {
		return mul(a, fastpow(a, Minus_1(n)));
	}
	else {
		matrix x = fastpow(a, Div_2(n));
		return mul(x, x);
	}
}


void read() {
	string s;
	cin >> s;
	n = read(s);
	cin >> m >> mod;
}

bool check(int a, int b) {
	for (int i = 0; i < m - 1; i++) {
		int x1 = (a >> i) & 1;
		int x2 = (a >> (i + 1)) & 1;
		int x3 = (b >> i) & 1;
		int x4 = (b >> (i + 1)) & 1;
		if (x1 == x2 && x1 == x3 && x1 == x4) return false;
	}
	return true;
}

int ans;
 
void run() {
	matrix fmul((1 << m), vector<int> ((1 << m), 0));
	for (int i = 0; i < (1 << m); i++) {
		for (int j = 0; j < (1 << m); j++) {
			if (check(i, j)) {
				fmul[i][j] = 1;
			}
		}
	}

	fmul = fastpow(fmul, Minus_1(n));

	ans = 0;
	for (auto i : fmul) {
		for (auto j : i) {
			ans += j;
			ans %= mod;
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