#include <bits/stdc++.h>

using namespace std;
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<long long> g;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		long long fg = 0;
		for (int j = 0; j < n; j++) {
			char x;
			cin >> x;
			if (i == j)
				x = '1';
			fg |= (1LL << j) * (x - '0');
		}
		g.push_back(fg);
	}
}

const int MAXN = (1 << 25);

long long used[MAXN];

long long calc(long long mask, int num) {
	if (mask < MAXN && used[mask] != -1) 
		return used[mask];
	for (int i = num; i >= 0; i--) {
		if ((mask >> i) & 1) {
			long long fans = calc(((mask ^ (1LL << i)) & g[i]), i - 1) + calc(mask ^ (1LL << i), i - 1) + 1;
			if (mask < MAXN)
				used[mask] = fans;
			return fans;
		}
	}
	return 0;
}

long long ans;
void run() {
	for (int i = 0; i < MAXN; i++) {
		used[i] = -1;
	}
	ans = calc((1LL << n) - 1, n - 1);
}

void write() {
	cout << ans + 1 << endl;
}

signed main() {
	//freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run();
	write();
	return 0;
}