#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}
#define int ll

int k, n; 
string now;
string s, t;
void read() {
	cin >> k >> n;
	cin >> now >> s >> t;
}

const int MAXK = 1e5 + 10;
const int INF = 1e18 + 228 + 1337;

int dp[MAXK][2][2];
int cnt[2][2];

int mul(int a, int b) {
	if (a == 0 || b == 0) return 0;
	if (a > INF / b) {
		return INF;
	}
	return a * b;
}

int add(int a, int b) {
	if (a + b > INF) {
		return INF;
	}
	return a + b;
}

void build() {
	for (int i = 0; i < 2; i++) for(int j = 0; j < 2; j++) cnt[i][j] = 0;
	for (auto i : s) {
		cnt[0][i - '0']++;
	} 
	for (auto i : t) {
		cnt[1][i - '0']++;
	}

	dp[0][0][0] = 1;
	dp[0][1][1] = 1;
	for (int start = 0; start < 2; start++) {
		for (int l = 1; l <= k; l++) {
			for (int i = 0; i < 2; i++) {
				for (int j = 0; j < 2; j++) {
					dp[l][start][i] = add(dp[l][start][i], mul(dp[l - 1][start][j], cnt[j][i]));
				}
			}
		}
	}
}

int get_cnt0(char start, int l) {
	l = k - l;
	return dp[l][start - '0'][0];
}

int get_cnt1(char start, int l) {
	l = k - l;
	return dp[l][start - '0'][1];
}

ll ans = 0;

void run() {
	build();
	int pos = 0;
	int l = 0;
	while (l < k) {
		int have = get_cnt1(now[pos], l);
		if (n > have) {
			n -= have;
			ans += get_cnt0(now[pos], l) + get_cnt1(now[pos], l);
			pos++;
		} else {
			now = (now[pos] == '0' ? s : t);
			pos = 0;
			l++;
		}
	}
	for (int i = 0; i < (int)now.size(); i++) {
		if (now[i] == '0') continue;
		n--;
		if (n == 0) {
			ans += i + 1;
			break;
		}
	}
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