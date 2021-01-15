#include <bits/stdc++.h>

using namespace std;
#define int long long
struct get_sum{
	vector<int> a;
	int n;
	get_sum() {

	}

	get_sum(int sz) {
		n = sz;
		a.assign(sz, 0);
	}

	void upd(int pos) {
		for (; pos < n; pos = (pos | (pos + 1)))
			a[pos] += 1;
	}

	int get(int r) {
		int ans = 0;
		for (; r >= 0; r = (r & (r + 1)) - 1) {
			ans += a[r];
		}
		return ans;
	}
};

const int INF = 1e9 + 10;
const int MAXN = 1010, MAXK = 60;
int dp[MAXN][MAXK];
int help[MAXN][MAXN];
int ans = INF;


int n, s, k;
vector<int> a;
void read() {
	cin >> n >> s >> k;
	a.resize(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
}

int get(int l, int r) {
	vector<int> help;
	for (auto i : a) {
		if (i >= l && i <= r)
			help.push_back(i);
	}

	int ans = 0;
	for (int i = 0; i < help.size(); i++) {
		for (int j = 0; j < i; j++) {
			ans += help[i] > help[j];
		}
	}
	return ans;
}

void build() {
	map <int, vector<int> > pos;
	for (int i = 0; i < n; i++) {
		pos[a[i]].push_back(i);
	}

	for (int l = 1; l <= s; l++) {
		get_sum st = get_sum(n);
		for (int r = l; r <= s; r++) {
			help[l][r] = help[l][r - 1];
			for (auto i : pos[r]) {
				help[l][r] += st.get(i);
			}
			for (auto i : pos[r]) {
				st.upd(i);
			}
		}
	}
}


void run() {
	build();

	for (int i = 0; i < MAXN; i++)
		for (int j = 0; j < MAXK; j++)
			dp[i][j] = INF;
	dp[0][0] = 0;
	for (int i = 1; i <= s; i++) {
		for (int j = 1; j <= min(i, k); j++) {
			for (int x = 0; x < i; x++) {
				dp[i][j] = min(dp[i][j], dp[x][j - 1] + help[x + 1][i]);
			}
		}
	}
	ans = dp[s][k];
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