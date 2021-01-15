#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 100000, MAXLOG = 21;
const int MAXLEN = 5;

int get_num(vector<int> num) {
	int ans = 0;
	for (auto i : num) {
		ans *= 10;
		ans += i;
	}
	return ans;
}

int get_nxt(int now) {
	vector<int> num;
	for (int i = 0; i < MAXLEN; i++) {
		num.push_back(now % 10);
		now /= 10;
	}
	sort(all(num));
	int y = get_num(num);
	reverse(all(num));
	int x = get_num(num);
	return x - y;
}

int nxt[MAXN][MAXLOG];

void build() {
	for (int i = 0; i < MAXN; i++) {
		nxt[i][0] = get_nxt(i);
	}
	for (int l = 1; l < MAXLOG; l++) {
		for (int i = 0; i < MAXN; i++) {
			nxt[i][l] = nxt[nxt[i][l - 1]][l - 1];
		}
	}
}

void print(int x) {
	string ans = "";
	for (int i = 0; i < MAXLEN; i++) {
		ans += '0' + x % 10;
		x /= 10;
	}
	reverse(all(ans));
	cout << ans << "\n";
}

void solve() {
	int need = 999999;
	int now;
	cin >> now;
	for (int i = MAXLOG - 1; i >= 0; i--) {
		if ((1 << i) > need) continue;
		need -= (1 << i);
		now = nxt[now][i];
	}
	print(now);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	build();
	int t;
	cin >> t;
	while (t--) {
		solve();
	}
	return 0;
}