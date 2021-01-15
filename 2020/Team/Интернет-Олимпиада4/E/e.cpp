#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e6 + 10;
int n;
int a[MAXN];

void check(int pos) {
	int now = 1;
	for (int i = 0; i < n; i++) {
		int x = a[(i + pos) % n];
		if (abs(x - now) > 1) return;
		now++; 
	}
	cout << "YES\n";
	cout << pos + 1 << "\n";
	exit(0);
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
	vector<int> cnt(n + 1);
	for (int i = 0; i < n; i++) {
		if (cnt[a[i]] == 3) {
			cout << "NO\n";
			return 0;
		}
		cnt[a[i]]++;
		if (a[i] <= 2) {
			check(i);
		}
	}
	cout << "NO\n";
	return 0;
}