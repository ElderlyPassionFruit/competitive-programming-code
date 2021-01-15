#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MOD = 1000000007;
 
int add(int a, int b) {
	a += b;
	if (a >= MOD)
		a -= MOD;
	return (a % MOD + MOD) % MOD;
}

int sub(int a, int b) {
	a -= b;
	if (a < 0)
		a += MOD;
	return (a % MOD + MOD) % MOD;
}

int mul(int a, int b) {
	a %= MOD;
	a += MOD;
	a %= MOD;
	b %= MOD;
	b += MOD;
	b %= MOD;
	return (ll) a * b % MOD;
}

int n, m, k;

void read() {
	cin >> n >> m >> k;
}

const int MAXN = 1e6 + 10;
int cnt[MAXN][2];
int fans[MAXN][2];

void build() {
	//cout << "row = " << endl;
	for (int i = 1; i <= n; i++) {
		cnt[i][0] = (((ll) (i - 1) * m + 1) * m + (ll) m * (m - 1) / 2) % MOD;
		//cout << cnt[i][0] << " ";
		fans[i][0] = 1;
	}
	//cout << endl;
	//cout << "col = " << endl;
	for (int i = 1; i <= m; i++) {
		cnt[i][1] = ((ll) i * n + (ll) n * (n - 1) * m / 2) % MOD;
		//cout << cnt[i][1] << " ";
		fans[i][1] = 1;
	}
	//cout << endl;
}

int ans = 0;
vector<int> haveX, haveY;

void calc() {
	for (int i = 0; i < k; i++) {
		char type;
		int x, y;
		cin >> type >> x >> y;
		//if (y == 1) continue;
		if (type == 'R') {
			fans[x][0] = mul(fans[x][0], y);
		} else {
			fans[x][1] = mul(fans[x][1], y);
		}
	}
	/*cout << "fans0 = " << endl;
	for (int i = 1; i <= n; i++) {
		cout << fans[i][0] << " ";
	}
	cout << endl;
	cout << "fans1 = " << endl;
	for (int i = 1; i <= m; i++) {
		cout << fans[i][1] << " ";
	}
	cout << endl;*/
	int x = n * m + 1;
	int y = n * m;
	if (x % 2 == 0) x /= 2;
	else y /= 2;
	x %= MOD;
	y %= MOD;
	ans = mul(x, y);
	//cout << "ans = " << ans << endl;
	for (int i = 1; i <= n; i++) {
		if (fans[i][0] != 1) {
			ans = sub(ans, cnt[i][0]);
			ans = add(ans, mul(fans[i][0], cnt[i][0]));
			haveX.push_back(i);
		}
	}
	//cout << ans << endl;
	for (int i = 1; i <= m; i++) {
		if (fans[i][1] != 1) {
			ans = sub(ans, cnt[i][1]);
			ans = add(ans, mul(fans[i][1], cnt[i][1]));
			haveY.push_back(i);
		}
	}
	//cout << ans << endl;
	//cout << endl;
	for (auto i : haveX) {
		for (auto j : haveY) {
			int x = add(mul(sub(i, 1), m), j);
			if (fans[i][0] == 0 && fans[j][1] == 0) {
				ans = add(ans, x);
				continue;
			} 
			if (fans[i][0] == 0 || fans[j][1] == 0) {
				ans = sub(ans, mul(x, add(sub(fans[i][0], 1), fans[j][1])));
				continue;
			}
			//cout << i << " " << j << endl;
			//cout << "x = " << x << endl;
			ans = sub(ans, mul(x, fans[i][0]));
			ans = sub(ans, mul(x, fans[j][1]));
			ans = add(ans, x);
			//cout << ans << endl;
			//cout << fans[i][0] << " " << fans[j][1] << endl;
			ans = add(ans, mul(x, mul(fans[i][0], fans[j][1])));
			//cout << ans << endl;
			//cout << endl;
		}
	}
}

void run() {
	build();
	calc();
}

void write() {
	cout << ans << "\n";
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

/*

2 1 2
S 1 0
R 2 0


*/