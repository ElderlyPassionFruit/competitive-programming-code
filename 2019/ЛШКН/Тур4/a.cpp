#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n, k, x;
const int MAXNUM = (1 << 10);
int a[MAXNUM];
int b[MAXNUM];

void read() {
	cin >> n >> k >> x;
	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;
		a[x]++;
	}
}

int ans1, ans2;

void run() {
	for (int test = 0; test < k; test++) { 
		
		int have = 0;
		for (int i = 0; i < MAXNUM; i++) {
			if (a[i] > 0) {
				int cnt = a[i] / 2 + (a[i] & 1) * (!(have & 1));
				b[i ^ x] += cnt;
				b[i] += a[i] - cnt;
				have += a[i]; 
			}
		}
		for (int i = 0; i < MAXNUM; i++) {
			a[i] = b[i];
			b[i] = 0;
		}

	}
	ans1 = 1e9, ans2 = -1e9;
	for (int i = 0; i < MAXNUM; i++) {
		if (a[i] > 0) {
			chkmin(ans1, i);
			chkmax(ans2, i);
		}
	}
}

void write() {
	cout << ans2 << " " << ans1 << endl;
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