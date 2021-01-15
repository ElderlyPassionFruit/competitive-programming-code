#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()
#define int ll
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k, mod;

int add(int a, int b) {
	a += b;
	if (a >= mod)
		a -= mod;
	return a;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += mod;
	return a;
}

int mul(int a, int b) {
	return (ll) a * b % mod;
}

void read() {
	cin >> k >> n >> mod;
}

const int MAXLOG = 11;
const int MAXN = 1010;

int ans;
bool used[MAXN];

vector<int> gen(int cnt) {
	vector<int> ans(cnt + 1, 0);
	for (int mask = 1; mask < (1 << cnt); mask++) {
		bool flag = true;
		for (int i = 1; i < cnt; i++) {
			if ((mask >> i) & 1) {
				if ((mask >> (i - 1)) & 1) flag = false;
				if (i >= 2 && ((mask >> (i - 2)) & 1)) flag = false;
			}
		}
		if (flag) {
			ans[__builtin_popcount(mask)]++;
		}
	}	
	return ans;
}
vector<int> fupd[MAXLOG];
int dp[MAXN];

void run() {
	for (int i = 1; i < MAXLOG; i++)
		fupd[i] = gen(i);
	dp[0] = 1;
	for (int i = 1; i <= n; i++) {
		if (used[i]) continue;
		int cnt = 0;
		for (int j = i; j <= n; j *= 2) {
			cnt++;
			used[j] = true;
		}
		for (int j = n; j >= 1; j--) {
			for (int k = 1; k < fupd[cnt].size() && j - k >= 0; k++) {
				dp[j] = add(dp[j], mul(dp[j - k], fupd[cnt][k]));
			}
		}
	}
	//cout << n << " " << k << " " << dp[k] << endl;
	//return;
	ans = dp[k];
}

void write() {
	cout << ans << endl;
}

void clear() {
	for (int i = 0; i < MAXN; i++)
		dp[i] = 0;
	for (int i = 0; i < MAXN; i++)
		used[i] = false;
}

vector<int> make(vector<int> a) {
	vector<int> ans;
	for (int i = 1; i < a.size(); i++)
		ans.push_back(a[i] - a[i - 1]);
	return ans;
}

int very_smart_solve(int n) {
	int x = (8 * n * n * n - 60 * n * n + n * ((n % 2) * 24 + (n % 4) * 12 + 127) - (n % 2) * 48 - (n % 4) * 48 - (n % 8) * 12 - (n % 16) * 3);
	assert(x % 48 == 0);
	return x / 48;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	mod = 1e18;
	//n = 16, k = 3;
	//run();
	//cout << ans << endl;
	//exit(0);

	/*for (int i = 5; i <= 1000; i++) {
		k = 3;
		n = i;
		run();
	
		if (ans != very_smart_solve(n)) {
			cout << i << " " << ans << " " << very_smart_solve(n) << endl;
		}
		clear();
	}
	return 0;
	*/
	vector<int> a;
	for (n = 64 + 7; n <= 1000; n += 64) {
		//for (k = 1; k <= n; k++) {
	
		k = 4;
			clear();
		//n += x;
			run();
		//n -= x;
			cout << ans << " ";
		//}
		a.push_back(ans);
	}
	return 0;
	while (a.size()) {
		a = make(a);
		for (auto i : a)
			cout << i << " ";
		cout << endl;
	}
	return 0;
	read();
	run();
	write();
	return 0;
}