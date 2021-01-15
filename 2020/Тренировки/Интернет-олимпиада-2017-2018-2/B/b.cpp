#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXX = 1e3 + 10, MAXK = 11;

bool used[MAXX][MAXK];
bool dp[MAXX][MAXK];
int par[MAXX][MAXK];

int x0, m, k;

bool calc(int x, int cnt) {
	if (used[x][cnt]) return dp[x][cnt];
	used[x][cnt] = true;
	for (int i = max(1, x - m); i < x; i++) {
		if (calc(i, 1) == 0) {
			dp[x][cnt] = 1;
			par[x][cnt] = i;
		} else if (!dp[x][cnt]) {
			par[x][cnt] = i;
		}
	}
	if (cnt + 1 < k) {
		if (calc(x, cnt + 1) == 0) {
			dp[x][cnt] = 1;
			par[x][cnt] = x;
		} else if (!dp[x][cnt]) {
			par[x][cnt] = x;
		}
	}
	return dp[x][cnt];
}

void no() {
	string ans = "";
	ans += 'I';
	ans += '\'';
	ans += 'm';
	ans += " giving up";
	cout << ans << endl;
	exit(0);
}

int readInt() {
	string s;
	cin >> s;
	if (s[0] == 'I') exit(0);
	int ans = 0;
	for (auto i : s) {
		ans *= 10;
		ans += i - '0';
	}
	return ans;
}

int query(int x) {
	cout << x << endl;
	return readInt();
}

int now, cnt;

void nxt(int x) {
	if (now == x) {
		cnt++;
	} else {
		now = x;
		cnt = 1;
	}
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> x0 >> m >> k;
	for (int i = 0; i <= x0; i++) {
		for (int cnt = 1; cnt < k; cnt++) {
			calc(i, cnt);
		}
	}
	now = x0, cnt = 1;
	while (par[now][cnt] != 0) {
		int need = query(par[now][cnt]);
		nxt(par[now][cnt]);
		nxt(need);
	}
	no();
	return 0;
}