#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) (x).begin(),(x).end()

string s1, s2, x;
int n, m, k;

const int MAXN = 110;
const int ALPHA = 26;

vector<int> prefixFunction(string & s) {
	int n = s.size();
	vector<int> p(n);
	for (int i = 1; i < n; i++) {
		int j = p[i - 1];
		while (j > 0 && s[i] != s[j]) j = p[j - 1];
		if (s[i] == s[j]) j++;
		p[i] = j;
	}
	return p;
}

int nxt[MAXN][ALPHA];

void buildNxt() {
	auto p = prefixFunction(x);
	/*cerr << "p = " << endl;
	for (auto i : p) {
		cerr << i << " ";
	}
	cerr << endl;*/
	for (int i = 0; i < k; i++) {
		for (int c = 0; c < ALPHA; c++) {
			if (i > 0 && c != x[i] - 'A') {
				nxt[i][c] = nxt[p[i - 1]][c];
			} else {
				//cerr << "c = " << c << " x[i] - a = " << x[i] - 'a' << endl;
				nxt[i][c] = i + (c == x[i] - 'A');
			}
		}
	}
	/*cerr << "nxt = " << endl;
	for (int i = 0; i < k; i++) {
		for (int c = 0; c < ALPHA; c++) {
			cerr << nxt[i][c] << " ";
		}
		cerr << endl;
	}*/
}

struct fpar{
	int len1, len2, len3;
	fpar() {}
	fpar(int _len1, int _len2, int _len3) {
		len1 = _len1, len2 = _len2, len3 = _len3;
	}
};

string ans;

int dp[MAXN][MAXN][MAXN];
fpar par[MAXN][MAXN][MAXN];

void relax(int len1, int len2, int len3, int val, fpar have) {
	if (len3 >= k) return;
	if (dp[len1][len2][len3] >= val) return;
	dp[len1][len2][len3] = val;
	par[len1][len2][len3] = have;
}

void calcDp() {
	for (int i = 0; i < MAXN; i++) for (int j = 0; j < MAXN; j++) for (int k = 0; k < MAXN; k++) dp[i][j][k] = -1, par[i][j][k] = {-1, -1, -1};
	dp[0][0][0] = 0;
	for (int len1 = 0; len1 < n; len1++) {
		for (int len2 = 0; len2 < m; len2++) {
			for (int len3 = 0; len3 < k; len3++) {
				int val = dp[len1][len2][len3];
				if (s1[len1] == s2[len2]) {
					int nxtLen3 = nxt[len3][s1[len1] - 'A'];
					//dp[len1 + 1][len2 + 1][nxtLen3] = max(dp[len1 + 1][len2 + 1][nxtLen3], dp[len1][len2][len3] + 1);
					relax(len1 + 1, len2 + 1, nxtLen3, val + 1, {len1, len2, len3});
				} 
				//dp[len1 + 1][len2][len3] = max(dp[len1 + 1][len2][len3], dp[len1][len2][len3]);
				relax(len1 + 1, len2, len3, val, par[len1][len2][len3]);
				//dp[len1][len2 + 1][len3] = max(dp[len1][len2 + 1][len3], dp[len1][len2][len3]);
				relax(len1, len2 + 1, len3, val, par[len1][len2][len3]);
			}
		}
	}
}

void makeAns() {
	int lenAns = 0;
	fpar now = {-1, -1, -1};
	for (int len1 = 0; len1 <= n; len1++) {
		for (int len2 = 0; len2 <= m; len2++) {
			for (int len3 = 0; len3 < k; len3++) {
				//lenAns = max(lenAns, dp[len1][len2][len3]);
				int val = dp[len1][len2][len3];
				if (val <= lenAns) continue;
				lenAns = val;
				now = par[len1][len2][len3];
			}
		}
	}
	//cerr << lenAns << endl;
	if (lenAns == 0) {
		cout << 0 << endl;
		exit(0);
	}
	ans = "";
	while (lenAns--) {
		assert(now.len1 != -1);
		ans += s1[now.len1];
		now = par[now.len1][now.len2][now.len3];
	}
	reverse(all(ans));
}

signed main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cout.precision(20);
	cin >> s1 >> s2 >> x;
	n = s1.size(), m = s2.size(), k = x.size();
	buildNxt();
	calcDp();
	makeAns();
	cout << ans << endl;
	return 0;
}