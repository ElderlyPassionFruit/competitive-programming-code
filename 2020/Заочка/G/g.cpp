#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

struct parent{
	int last, need;
	parent() {}
	parent(int a, int b) {
		last = a, need = b;
	}
};

using lnum = vector<int>;

const int MAXN = 1e3 + 10;
int n;
lnum a[MAXN], b;
bool dp[MAXN][MAXN];
parent p[MAXN][MAXN];

int ord[MAXN], nord[MAXN];
int c[MAXN], nc[MAXN];
int cnt[MAXN], pref[MAXN];

lnum readInt() {
	string s;
	cin >> s;
	reverse(all(s));
	lnum ans;
	for (auto i : s)
		ans.push_back(i - '0');
	return ans;
}

int x = 0;

void read() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		a[i] = readInt();
	}
	b = readInt();
	for (int i = 0; i < n; i++)
		chkmax(x, a[i].size());
	chkmax(x, b.size());
	for (int i = 0; i < n; i++) {
		while (a[i].size() < x)
			a[i].push_back(0);
	}
	while (b.size() < x)
		b.push_back(0);
}

void build() {
	for (int i = 0; i < MAXN; i++) {
		for (int j = 0; j < MAXN; j++) {
			dp[i][j] = false;
		}
	}
}

int recalc(int pos, int s, int num) {
	for (int i = 0; i < n; i++)
		cnt[i] = 0;

	int x = 0;	
	for (int i = 0; i < n; i++)
		if (a[ord[i]][pos] == num)
			cnt[c[ord[i]]]++, x++;
	
	pref[0] = s;
	
	for (int i = 1; i < n; i++)
		pref[i] = pref[i - 1] + cnt[i - 1];
	
	for (int i = 0; i < n; i++) {
		if (a[ord[i]][pos] == num)
			nord[pref[c[ord[i]]]++] = ord[i];
	}
	return x;
}

void resort(int pos) {
	recalc(pos, recalc(pos, 0, 1), 0);
	
	for (int i = 0; i < n; i++)
		ord[i] = nord[i];

	int cc = 0;
	for (int i = 0; i < n; i++) {
		if (i == 0 || c[ord[i]] != c[ord[i - 1]] || a[ord[i]][pos] != a[ord[i - 1]][pos])
			nc[ord[i]] = cc++;
		else
			nc[ord[i]] = nc[ord[i - 1]];
	}
	for (int i = 0; i < n; i++)
		c[i] = nc[i];
}

void calc_dp() {
	dp[0][0] = true;
	p[0][0] = {0, 0};
	for (int i = 0; i < n; i++)
		ord[i] = i, c[i] = 0;

	for (int i = 0; i < x; i++) {
		int cnt = 0;
		for (int j = 0; j < n; j++) {
			cnt += a[j][i];
		}
		int next0 = 0;
		int next1 = cnt;
		int have = cnt;
		for (int j = 0; j <= n; j++) {
			if (dp[i][j]) {
				if (have % 2 == b[i] % 2) {
					dp[i + 1][next0] = true;
					p[i + 1][next0] = {j, 0};
				}
				if ((n - have) % 2 == b[i] % 2) {
					dp[i + 1][next1] = true;
					p[i + 1][next1] = {j, 1};
				}
			}
			if (j == n) continue;
			if (a[ord[j]][i]) next0++, have--;
			if (!a[ord[j]][i]) next1++, have++;
		}
		resort(i);
	}
}

string ans;

void make_ans() {
	int now = -1;
	for (int i = 0; i <= n; i += 2) {
		if (dp[x][i])
			now = i;
	}
	if (now == -1) {
		ans = "-1";
		return;
	}
	ans = "";
	for (int pos = x; pos > 0; pos--) {
		ans += p[pos][now].need + '0';
		now = p[pos][now].last;
	}
	reverse(all(ans));
	while (ans.size() > 1 && ans.back() == '0') ans.pop_back();
	reverse(all(ans));
}

void run() {
	build();
	calc_dp();
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