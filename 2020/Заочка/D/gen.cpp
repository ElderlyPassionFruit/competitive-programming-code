#include <bits/stdc++.h>

using namespace std;
#define int long long
#define pb push_back
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

mt19937 rnd(time(0));

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

const int INF = 2;

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n, k;
	n = get(3, 5);
	k = 1;
	cout << n << " " << k << "\n";
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < k; i++) {
			cout << get(-INF, INF) << " ";
		}
		cout << "\n";
		for (int i = 0; i < k; i++) {
			cout << get(-INF, INF) << " ";
		}
		cout << "\n";
	}
	for (int i = 2; i <= n; i++) {
		cout << (i - 1) << " " << i << "\n";
	}
	return 0;
}