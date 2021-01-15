#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

const int MAXN = 210;

int n, k;
int a[MAXN][MAXN];

void read() {
	cin >> n >> k;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> a[i][j];
		}
	}
}

bool check_n(int k) {
	bool flag = true;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			cnt += (a[i][j] == k);
		}
		flag &= (cnt >= 2);
	}
	if (flag) return true;
	flag = true;
	for (int j = 0; j < n; j++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cnt += (a[i][j] == k);
		}
		flag &= (cnt >= 2);
	}
	if (flag) return true;
	return false;
}

bool check_n_1(int k) {
	bool flag = true;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			cnt += (a[i][j] == k);
		}
		flag &= (cnt >= 1);
	}

	bool flag2 = false;
	for (int j = 0; j < n; j++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cnt += (a[i][j] == k);
		}
		flag2 |= (cnt >= 2);
	}

	if (flag && flag2) return true;
	
	flag = true;
	for (int j = 0; j < n; j++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cnt += (a[i][j] == k);
		}
		flag &= (cnt >= 1);
	}

	flag2 = false;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			cnt += (a[i][j] == k);
		}
		flag2 |= (cnt >= 2);
	}

	if (flag && flag2) return true;
	return false;
}

bool check_n_2(int k) {
	int cnt2 = 0;
	for (int i = 0; i < n; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			cnt += (a[i][j] == k);
		}
		cnt2 += (cnt >= 2);
	}
	if (cnt2 >= 2) return true;
	cnt2 = 0;
	for (int j = 0; j < n; j++) {
		int cnt = 0;
		for (int i = 0; i < n; i++) {
			cnt += (a[i][j] == k);
		}
		cnt2 += (cnt >= 2);
	}
	if (cnt2 >= 2) return true;
	return false;
}

pair<int, int> ans;

void run() {
	ans = {0, 0};
	for (int i = 1; i <= k; i++) {
		if (check_n(i)) {
			ans = {n, i};
			return;
		}
	}
	cout << check_n_1(2) << endl;
	for (int i = 1; i <= k; i++) {
		if (check_n_1(i)) {
			ans = {n + 1, i};
			return;
		}
	}
	for (int i = 1; i <= k; i++) {
		if (check_n_2(i)) {
			ans = {n + 2, i};
			return;
		}
	}
}

void write() {
	cout << ans.first << " " << ans.second << endl;
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