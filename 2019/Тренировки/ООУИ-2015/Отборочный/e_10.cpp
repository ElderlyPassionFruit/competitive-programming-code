#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MOD = 1e9 + 7;
int a, b, c, d;
void read() {
	cin >> a >> b >> c >> d;
}

bool check(int n, int k) {
	if (k > n)
		return false; 
	while(n >= 0 && k >= 0 && n + k > 0) {
		if (n % 2 == 0 && k % 2 == 1) {
			return false;
		}
		n /= 2;
		k /= 2;
	}
	return true;
}

int fact(int x) {
	int ans = 1;
	for (int i = 0; i < x; i++)
		ans *= x + 1;
	return ans;
}

int c_n_k(int a, int b) {
	return fact(a) / (fact(b) * fact(a - b));
}

int pows(int a, int n) {
	int ans = 1;
	for (int i = 0; i < n; i++) {
		ans *= a;
		ans %= MOD;
	}
	return ans;
}

int ans = 0;

void run() {
	if (d == 1e18) {
		int x = 0;
		while (b) {
			x++;
			b /= 2;
		}
		ans = pows(3, x);
		return;
	}
	for (int i = a; i <= b; i++) {
		for (int j = c; j <= d; j++) {
		//	cout << "i = " << i << " j = " << j << " check = " << check(i, j) << " c_n_k = " << c_n_k(i, j) << endl;
			ans += check(i, j);
		}
	}
}

void write() {
	cout << ans % MOD << endl;
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