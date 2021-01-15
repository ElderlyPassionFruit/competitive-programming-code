#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> help;

void read() {
	cin >> n;
	help.resize(n);
	for (int i = 1; i < n; i++) {
		cin >> help[i];
	}
}

const int MOD = 988244353;

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
	return a * b % MOD;
}

int binpow(int a, int n) {
	if (n == 0) return 1;
	if (n % 2 == 0) {
		int x = binpow(a, n / 2);
		return mul(x, x);
	}
	else {
		return mul(a, binpow(a, n - 1));
	}
}

const int MAXN = 2e5 + 10;
int p[MAXN];
int sz[MAXN];

vector<int> ans;

void run() {
	p[0] = -1;
	sz[0] = 1;
	int sum_v = 2;
	int sum_n_v = 1;

	for (int i = 1; i < n; i++) {
		p[i] = help[i] - 1;
		sz[i] = 1;
		int x = p[i];
		while (x != -1) {
			sum_v = sub(sum_v, binpow(2, sz[x]));
			sum_n_v = sub(sum_n_v, binpow(2, i - sz[x]));
			x = p[x]; 
		}

		sum_n_v = mul(sum_n_v, 2);
		x = p[i];
		while (x != -1) {
			sz[x]++;
			sum_n_v = add(sum_n_v, binpow(2, i + 1 - sz[x]));
			sum_v = add(sum_v, binpow(2, sz[x]));
			x = p[x];
		}

		sum_v = add(sum_v, 2);
		sum_n_v = add(sum_n_v, binpow(2, i));
		int fans = 0;

		fans = add(fans, mul(binpow(2, i + 1), i + 1));
		fans = sub(fans, sum_v);
		fans = add(fans, sum_n_v);
		fans = sub(fans, i);
		ans.push_back(fans);
	}
}

void write() {
	for (auto i : ans)
		cout << i << " ";
	cout << endl;
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