#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MOD = 1e9 + 7;

const int MAXN = 3e5 + 10;
int n;
int a[MAXN];

void read() {
	cin >> n;
	for (int i = 0; i < n; i++)
		cin >> a[i];
	sort(a, a + n);
}

int pows[MAXN];
int ans;
void run() {
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows[i] = pows[i - 1] * 2 % MOD;
	}
	for (int i = 1; i < MAXN; i++)
		pows[i] = (pows[i - 1] + pows[i]) % MOD;

	int sum = 0;
	sum += a[0];
	int mul = 1;
	ans = 0;
	for (int i = 1; i < n; i++) {
		ans = (ans + (mul * a[i] % MOD - sum) % MOD + MOD) % MOD;
		mul *= 2;
		mul += 1;
		mul %= MOD;
		sum *= 2;
		sum += a[i];
		sum %= MOD;
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