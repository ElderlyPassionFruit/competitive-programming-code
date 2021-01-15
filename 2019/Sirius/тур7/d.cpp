#include <bits/stdc++.h>

using namespace std;
#define int long long

const int MAXN = 50010;
const int INF = 1e15;
const int MOD = 1e9 + 7;
const int b = 47;

pair <string, int> arr[MAXN];

int dp[MAXN];
int pows[MAXN];
int hashs[MAXN];
int help_hashs[201][50010];
int m, n, l;
string s;

void make() {
	pows[0] = 1;
	for (int i = 1; i < MAXN; i++) {
		pows[i] = (pows[i - 1] * b) % MOD;
	}
	hashs[0] = 0;
	for (int i = 1; i <= m; i++) {
		hashs[i] = (hashs[i - 1] + pows[i] * s[i - 1]) % MOD;
	}

	for (int j = 0; j < n; j++) {
		help_hashs[j][0] = 0;
		for (int i = 1; i <= arr[j].first.size(); i++) {
			help_hashs[j][i] = (help_hashs[j][i - 1] + arr[j].first[i - 1] * pows[i]) % MOD;
		}
	}
}

int get_hash(int l, int r) {
	return ((((hashs[r] - hashs[l - 1]) % MOD + MOD) % MOD) * pows[MAXN - 5 - r]) % MOD;
}

int get_hash(int j, int l, int r) {
	return ((((help_hashs[j][r] - help_hashs[j][l - 1]) % MOD + MOD) % MOD) * pows[MAXN - 5 - r]) % MOD;	
}

void read() {
	cin >> m >> n >> l;
	cin >> s;
	for (int i = 0; i < n; i++) {
		cin >> arr[i].second >> arr[i].first;
	}	
	make();
}

int pref(int j, int pos) {
	int sz = arr[j].first.size();
	int l = 0;
	int r = min(sz, m - pos + 1) + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int h1 = get_hash(pos, pos + mid - 1);
		int h2 = get_hash(j, 1, mid);
		if (h1 == h2) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	return l;
}

int suff(int j, int pos) {
	int sz = arr[j].first.size();
	int l = 0, r = min(sz, pos) + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		int h1 = get_hash(pos - mid + 1, pos);
		int h2 = get_hash(j, sz - mid + 1, sz);
		if (h1 == h2) {
			l = mid;
		}
		else {
			r = mid;
		}
	}
	return l;
}

void run2() {
	for (int i = 0; i < MAXN; i++)
		dp[i] = INF;
	dp[0] = 0;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < n; j++){
			int len1 = suff(j, i);
			//cerr << "i = " << i << " j = " << j << " suff = " << len1 << " ";
			int cost = arr[j].second;
			for (int len = 1; len <= len1; len++)
				dp[i] = min(dp[i], dp[i - len] + cost);
			len1 = pref(j, i);
			//cerr << "pref = " << len1 << endl;
			for (int len = 2; len <= len1; len++)
				dp[i + len - 1] = min(dp[i + len - 1], dp[i] + cost);
		}	
	}
	/*cerr << "dp = " << endl;
	for (int i = 0; i <= m; i++) {
		cerr << dp[i] << " ";
	}
	cerr << endl;*/
}

void write() {
	if (dp[m] == INF) {
		dp[m] = -1;
	}
	cout << dp[m] << endl;
}

signed main() {
	freopen("typing.in", "r", stdin);
	freopen("typing.out", "w", stdout);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	read();
	run2();
	write();
	return 0;
} 