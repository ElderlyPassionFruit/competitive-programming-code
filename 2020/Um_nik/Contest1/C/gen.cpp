#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

int get(int l, int r) {
	return rnd() % (r - l + 1) + l;
}

int n;
vector<vector<bool>> g;

bool check(int mask) {
	vector<bool> used(n, true);
	for (int i = 0; i < n; i++) {
		if ((mask >> i) & 1) {
			for (int j = 0; j < n; j++) {
				used[j] = used[j] && g[i][j];
			}
		}
	}
	int cnt = 0;
	for (auto i : used) cnt += i;
	return cnt == 1;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n = get(1, 4);
	cout << n << endl;
	for (int i = 0; i < n; i++) {
		cout << get(1, 5) << " ";
	}
	cout << endl;
	return 0;
}