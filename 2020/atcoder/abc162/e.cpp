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

int n, k;

void read() {
	//cin >> n >> k;
}

int ans;

int gcd(vector<int> have) {
	int ans = have[0];
	for (int i = 1; i < (int)have.size(); i++)
		ans = __gcd(ans, have[i]);
	if (ans != 1) return 0;
	return ans;
}

void solve(vector<int> have, int n, int k) {
	if (have.size() == n) {
		ans += gcd(have);
		return;
	}
	have.push_back(0);
	for (int i = 0; i <= k; i++) {
		solve(have, n, k);
		have[have.size() - 1]++;
	}
}

int brute(int n, int k) {
	ans = 0;
	solve({}, n, k);
	return ans;
}

void run() {
	for (int n = 1; n <= 10; n++) {
		for (int k = 1; k <= 5; k++) {
			cout << brute(n, k) << " ";
		}
		cout << endl;
	}
}

void write() {

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