#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll
const int MAXN = 1000;
bool used[MAXN * 2];

void brute() {
	//int J = 0;
	int cnt = 0;
	for (int i = 1; i < MAXN; i++) {
		if (used[i]) continue;
		for (int j = i + 1; j < MAXN; j++) {
			if (used[i]) break;
			if (used[j]) continue;
			for (int k = j + 1; k < MAXN; k++) {
				if (used[i]) break;
				if (used[j]) break;
				if (used[k]) continue;
				if (i ^ j ^ k) continue;
				//cout << i << " " << j << " " << k << endl;
				//I = i, J = j, K = k;
				//if (j - J != 1 && j - J != 2 && j - J != -2)
				cout << ((j >> 3) & 1) << " ";
				cnt++;
				if (cnt % 32 == 0) cout << endl;
				//J = j;
				used[i] = true;
				used[j] = true;
				used[k] = true;
			}
		}
	}
}

void precalc() {
	brute();
}

void solve() {
	int n;
	cin >> n;
}

signed main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	precalc();
	return 0;
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}