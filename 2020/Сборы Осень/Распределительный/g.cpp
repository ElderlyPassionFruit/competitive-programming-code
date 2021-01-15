#include <bits/stdc++.h>

using namespace std;
//#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 1e6 + 10;

int len(int x) {
	int ans = 0;
	while (x) {
		ans++;
		x /= 10;
	}
	return ans;
}

int pows[20];
int Len[MAXN];
bool not_prime[MAXN];

void precalc() {
	not_prime[0] = 1;
	not_prime[1] = 1;

	for (int i = 2; i < MAXN; i++) {
		if (not_prime[i]) continue;
		for (int j = 2 * i; j < MAXN; j += i)
			not_prime[j] = 1;
	}

	pows[0] = 1;
	for (int i = 1; i < 10; i++)
		pows[i] = pows[i - 1] * 10;

	for (int i = 0; i < MAXN; i++)
		Len[i] = len(i);
}

string n;
int k;

void read() {
	cin >> n >> k;
}

const int MOD = 1e9 + 7;

int add(int a, int b) {
	return (a + b) % MOD;
	a += b;
	if (a >= MOD)
		a -= MOD;
	return a;
}

int dp[MAXN];

void fassert(bool flag) {
	if (flag) {
		while (1);
	}
}

int getint(string s) {
	int ans = 0;
	for (auto i : s) {
		ans *= 10;
		ans += i - '0';
	}
	return ans;
}

void run() {
	dp[0] = 1;
	for (int i = 1; i <= n.size(); i++) {
		string s = "";
		for (int j = i; j > max(0, i - k); j--) {
			s = n[j - 1] + s;
			//cout << "i = " << i << " s = " << s << endl; 
			if (!not_prime[getint(s)] && s[0] != '0') {
				dp[i] = add(dp[i], dp[j - 1]);
			}
		}
	}

}

void write() {
	cout << dp[n.size()] << endl;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	precalc();
	read();
	run();
	write();
	return 0;
}