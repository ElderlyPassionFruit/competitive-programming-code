#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

const int MAXLOG = 24;
const int MAXN = (1 << MAXLOG) + 228;
const int N = 1 << MAXLOG;

int dp[MAXN];

void add(vector<char> s) {
	int a = 1 << (s[0] - 'a');
	int b = (s.size() >= 2 ? 1 << (s[1] - 'a') : 0);
	int c = (s.size() >= 3 ? 1 << (s[2] - 'a') : 0);
	if (a) dp[a]++;
	if (b) dp[b]++;
	if (c) dp[c]++;
	if (a && b) dp[a | b]--;
	if (a && c) dp[a | c]--;
	if (b && c) dp[b | c]--;
	if (a && b && c) dp[a | b | c]++;
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		string s;
		cin >> s;
		vector<char> have;
		for (auto x : s) have.push_back(x);
		sort(all(have));
		have.resize(unique(all(have)) - have.begin());
		add(have);
	}
	for (int k = 0; k < MAXLOG; k++) {
		for (int mask = 0; mask < N; mask++) {
			if ((mask >> k) & 1) {
				dp[mask] += dp[mask ^ (1 << k)];
			}
		}
	}
	ll ans = 0;
	for (int i = 0; i < N; i++) {
		ans ^= (ll) dp[i] * dp[i]; 
	}
	cout << ans << endl;
	return 0;
}