#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
int a[360];

void read() {
	cin >> n;
	for (int i = 0; i < 360; i++) a[i] = 0;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		assert(a[x] == 0);
		a[x] = 1;
	}
}

int g[360];
bool used[360], gr[360];

int calc(int d) {
	for (int i = 0; i < 360; i++) g[i] = -1, gr[i] = false;
	for (int i = 0; i < 360; i++) {
		if (!a[i]) continue;
		int j = (i + d) % 360;
		if (a[j]){
			g[i] = j;
			gr[j] = true;
		}
	}

	int ans = 0;

	for (int i = 0; i < 360; i++)
	used[i] = false;

	for (int i = 0; i < 360; i++) {
		if (g[i] == -1) continue;
		if (gr[i]) continue;
		int v = i;
		int fans = 0;
		while (v != -1 && !used[v]) {
			used[v] = true;
			fans++;
			v = g[v];
		}
		ans += (fans / 2) * 2;
	}

	for (int i = 0; i < 360; i++) {
		if (g[i] == -1) continue;
		int v = i;
		int fans = 0;
		while (v != -1 && !used[v]) {
			used[v] = true;
			fans++;
			v = g[v];
		}
		ans += (fans / 2) * 2;
	}
	return ans;
}

int ans;

void run() {
	ans = 0;
	for (int d = 1; d <= 359; d++) {
		chkmax(ans, calc(d));
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