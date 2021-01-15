#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

void no() {
	cout << -1 << endl;
	exit(0);
}

const int MAXN = 7e4 + 10;
int n, s;
pair<int, int> a[MAXN];

bitset<MAXN> dp;
bitset<MAXN> used;
int first[MAXN];

int ans[MAXN];
vector<int> fans[MAXN];
bool have[MAXN];

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> n >> s;
	for (int i = 0; i < n; i++) {
		cin >> a[i].first;
		a[i].second = i;
	}
	sort(a, a + n);
	if (s < a[n - 1].first) no();
	s -= a[n - 1].first;
	fill(first, first + s, -1);
	dp[0] = 1;
	for (int i = 0; i < n - 1; i++) {
		used = ((dp << a[i].first) | dp) ^ dp;
		for (int bit = used._Find_first(); bit < MAXN; bit = used._Find_next(bit)) {
			first[bit] = i;
		}
		dp = (dp << a[i].first) | dp;
	}
	if (!dp[s]) no();
	fill(ans, ans + n, 0);
	while (s) {
		ans[a[first[s]].second] = a[first[s]].first;
		have[first[s]] = true;
		s -= a[first[s]].first;
	}
	int last = -1;
	for (int i = 0; i < n; i++) {
		if (have[i]) continue;
		if (last == -1) {
			ans[a[i].second] = a[i].first;
		} else {
			ans[a[i].second] = a[i].first - a[last].first;
			fans[a[i].second] = {a[last].second};
		}
		last = i;
	}
	for (int i = 0; i < n; i++) {
		cout << ans[i] << " ";
		cout << fans[i].size();
		for (auto x : fans[i]) {
			cout << " " << x + 1;
		}
		cout << endl;
	}
	return 0;
}
