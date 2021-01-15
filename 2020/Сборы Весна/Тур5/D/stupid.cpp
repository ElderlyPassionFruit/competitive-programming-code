#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

#define int short int

const int MAXN = 100, MAXA = 10;
const int INF = 30000;
string s;
int n;
int dp[MAXN][MAXN];
int pos[MAXN];
bool need[MAXN];
int last[MAXN][MAXA];
int pref[MAXN];
int cnt;

void read() {
	cin >> n >> s;
}

int ans;

void build() {
	ans = 0;
	reverse(all(s));
	while (!s.empty() && s.back() == 'e') {
		s.pop_back();
		ans++;
		n--;
	}
	if (s.empty()) {
		cout << ans << endl;
		exit(0);
	}
	reverse(all(s));
	for (auto i : s) {
		ans += 2 * (i == 'e');
	}
	string ns = "";
	ns += s[0];
	for (int i = 1; i < n; i++) {
		if (s[i] == 'e') continue;
		ns += s[i];
		if (s[i - 1] == 'e') {
			need[ns.size() - 1] = true;
		}
	}
	s = ns;
	n = s.size();
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dp[i][j] = INF;
		} 
	}
	dp[0][0] = 0;
	cnt = 0;
	for (int i = 0; i < n; i++) {
		if (need[i]) {
			pos[cnt++] = i;
		}
	}
	for (int i = 0; i < n; i++) {
		pref[i] += need[i];
	}
	for (int i = 1; i < n; i++) {
		pref[i] += pref[i - 1];
	}
	for (int i = 0; i < MAXA; i++)
		last[n - 1][i] = -1;
	for (int i = n - 2; i >= 0; i--) {
		for (int j = 0; j < MAXA; j++) {
			last[i][j] = last[i + 1][j];
		}
		last[i][s[i + 1] - 'a'] = i + 1;
	}
}

void relax(int pos, int cnt, int cost) {
	if (pos == -1) return;
	chkmin(dp[pos][cnt], cost); 
}

void calc() {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < cnt; j++) {
			if (dp[i][j] == INF) continue;
			for (int c = 0; c < MAXA; c++) {
				relax(last[i][c], j, dp[i][j] + 2);
				int add = pref[i] - j;
				if (add == 0) continue;
				int len = i - pos[j];
				int nxt = last[pos[j]][c];
				if (nxt < i) continue;
				relax(nxt, j + add, dp[i][j] + len + 2);
			}
		}
	}
}

void make_ans() {
	int fans = INF;
	for (int i = 0; i < n; i++) {
		if (pref[i] != cnt) continue;
		for (int j = 0; j <= cnt; j++) {
			chkmin(fans, dp[i][j] + i - pos[j]);
		}
	}
	ans += fans;
}

void run() {
	build();
	calc();
	make_ans();
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