#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> g;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		int fg = 0;
		for (int j = 0; j < n; j++) {
			char x;
			cin >> x;
			if (i == j)
				x = '1';
			fg |= (1 << j) * (x - '0');
		}
		g.push_back(fg);
	}
}

bool check(int mask, int r) {
	int fmask = (1 << r) - 1;
	for (int i = 0; i < r; i++) {
		if ((mask >> i) & 1)
			fmask &= g[i];
	}
	return mask == (mask & fmask);
}

const int MAXN = (1 << 25);
bool good_maskL[MAXN];
int dp[MAXN];

int calc(int mask, int l, int r) {
	int fmask = (1 << (l + r)) - 1;
	for (int i = 0; i < l; i++) {
		if ((mask >> i) & 1)
			fmask &= g[i + r];
	}
	if ((fmask & (mask << r)) != (mask << r))
		return 0;
	fmask &= (1 << r) - 1;
	return dp[fmask];
}

long long ans;
void run() {
	int l = n / 2;
	int r = n - l;

	good_maskL[0] = 1;
	for (int i = 1; i < (1 << r); i++) {
		good_maskL[i] = check(i, r);
	}

	for (int mask = (1 << r) - 1; mask >= 0; mask--)
		dp[mask] = good_maskL[mask];
		
	for (int i = 1; i <= r; i++) {
		for (int mask = (1 << r) - 1; mask >= 0; mask--) {
			if ((mask >> (i - 1)) & 1) {
				dp[mask] = dp[mask] + dp[mask ^ (1 << (i - 1))];
			}
		}
	}

	ans = 0;

	for (int mask = 0; mask < (1 << l); mask++) {
		ans += calc(mask, l, r);
	}
}

void write() {
	cout << ans << endl;
}

signed main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}