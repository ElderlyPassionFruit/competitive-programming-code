#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;
using ld = long double;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

int n;
vector<int> l, r;

void read() {
	cin >> n;
	l.resize(n);
	for (auto &i : l)
		cin >> i;
	r.resize(n);
	for (auto &i : r)
		cin >> i;
}

vector<int> have;

void build() {
	for (int i = 1; i < n; i++)
		chkmax(l[i], l[i - 1] + 1);
	for (int i = n - 2; i >= 0; i--)
		chkmin(r[i], r[i + 1] - 1);
	for (int i = 0; i < n; i++)
		r[i]++;
	for (int i = 0; i < n; i++) {
		if (r[i] <= l[i]) {
			cout << 0 << endl;
			exit(0);
		}
		have.push_back(l[i]), have.push_back(r[i]);
	}
	sort(all(have));
	have.resize(unique(all(have)) - have.begin());
}

int ans = 0;

const int MAXN = 310;
int dp[MAXN * 2][MAXN];

void calc() {
	dp[0][0] = 1;
	for (int i = 0; i < have.size(); i++) {
		for (int j = 0; j < n; j++) {
			if (dp[i][j] == 0) continue;
			for (int now = 0; now <= j; now++) {
				
			}
		}
	}
	ans = dp[have.size()][0];
}

void run() {
	build();
	calc();
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