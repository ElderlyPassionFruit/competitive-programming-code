#include <bits/stdc++.h>

using namespace std;
#define int long long
int n, m;
const int MAXN = 510;	
int dp1[MAXN][MAXN], dp2[MAXN][MAXN];
void read() {
	int cnt0 = 0, cnt1 = 0;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> dp1[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> dp2[i][j];
		}
	}
	for (int i = 0; i < n; i++) {
		int cnt0 = 0, cnt1 = 0;
		for (int j = 0; j < m; j++) {
			cnt0 += dp1[i][j];
			cnt1 += dp2[i][j];
		}
		if (cnt0 % 2 != cnt1 % 2) {
			cout << "No";
			return;
		}
	}
	for (int j = 0; j < m; j++) {
		int cnt0 = 0, cnt1 = 0;
		for (int i = 0; i < n; i++) {
			cnt0 += dp1[i][j];
			cnt1 += dp2[i][j];
		}
		if (cnt0 % 2 != cnt1 % 2) {
			cout << "No";
			return;
		}
	}
	cout << "Yes";
}

void run() {

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