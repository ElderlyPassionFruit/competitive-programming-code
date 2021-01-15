#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXN = 1e5 + 10;
const int MAXM = 20;

int n, m, d;

vector<int> a[MAXN];

int maskNow = 0;
int cnt[MAXM];

void add(int x) {
	cnt[x]++;
	if (cnt[x] == 1) {
		maskNow ^= 1 << x;
	}
}

void del(int x) {
	cnt[x]--;
	if (cnt[x] == 0) {
		maskNow ^= 1 << x;
	}
}

bool used[1 << MAXM];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> m >> d;
	maskNow = (1 << m) - 1;
	for (int i = 0; i < m; i++) {
		int sz;
		cin >> sz;
		for (int j = 0; j < sz; j++) {
			int x;
			cin >> x;
			a[x].push_back(i);
		}
	}
	for (int i = 1; i <= d; i++) {
		for (auto x : a[i]) {
			add(x);
		}
	}
	used[maskNow] = true;
	for (int i = d + 1; i <= n; i++) {
		for (auto x : a[i]) {
			add(x);
		}
		for (auto x : a[i - d]) {
			del(x);
		}
		used[maskNow] = true;
	}
	for (int mask = (1 << m) - 1; mask >= 0; mask--) {
		if (!used[mask]) continue;
		for (int bit = 0; bit < m; bit++) {
			if ((mask >> bit) & 1) {
				used[mask ^ (1 << bit)] |= used[mask];
			}
		}
	}
	int ans = m;
	for (int i = 0; i < (1 << m); i++) {
		if (!used[i]) {
			ans = min(ans, __builtin_popcount(i));
		}
	} 
	cout << ans << endl;
	return 0;
}