#include <bits/stdc++.h>

using namespace std;
const int MAXN = 2 * 1e6 + 10;
const int MOD = 998244353;

pair <int, int> a[MAXN];
int n;
int max_len[MAXN];
int dp[MAXN];
vector <int> help[MAXN];
unordered_map <int, int> coords(MAXN);
int help2[MAXN];


void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> a[i].first >> a[i].second;
	}
}

int ans;
void run() {
	int pos = 0;
	for (int j = 0; j < n; j++) {
		auto i = a[j];
		help2[pos++] = i.first;
		help2[pos++] = i.second;
	}

	sort(help2, help2 + pos);

	int last = -1;
	int cnt = 0;
	for (int j = 0; j < pos; j++) {
		int i = help2[j];
		if (i != last)
			coords[i] = ++cnt;
		last = i;
	}

	for (int j = 0; j < n; j++){
		auto i = a[j];
		help[coords[i.second]].push_back(coords[i.first]);
	}

	for (int i = 1; i <= cnt; i++) {
		max_len[i] = max_len[i - 1];
		dp[i] = dp[i - 1];

		if (((int) help[i].size()) == 0)
			continue;

		for (auto j : help[i]) {
			if (max_len[j] + 1 > max_len[i]) {
				max_len[i] = max_len[j] + 1;
				dp[i] = max(dp[j], 1);
			}
			else if (max_len[j] + 1 == max_len[i]) {
				dp[i] += max(dp[j], 1);
				if (dp[i] > MOD)
					dp[i] -= MOD;
			}
		}
	}
	ans = dp[cnt];
}

void write() {
	cout << ans << endl;
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