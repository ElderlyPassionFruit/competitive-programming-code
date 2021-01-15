#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using ull = unsigned long long;
#define all(x) x.begin(), x.end()

template <typename T1, typename T2> inline void chkmin(T1 &x, const T2 & y) {if (x > y) x = y;}
template <typename T1, typename T2> inline void chkmax(T1 &x, const T2 & y) {if (x < y) x = y;}

void no() {
	cout << "-1" << endl;
	exit(0);
} 

int len, n, k;
string s;
void read() {
	cin >> len >> n >> k;
	cin >> s;
	len++;
	s += "+";
}

int get(int l, int r, int cnt) {
	l--;
	r--;
	if (l == r) {
		if (s[l] == '0' || cnt > 0) return 0;
		if (s[l] == '+') return n + 1;
		return s[l] - '0';
	}
	string have = "";
	for (int i = l; i <= r; i++) {
		if (s[i] != '+') {
			have += s[i];
			continue;	
		}
		if (cnt == 0) return n + 1;
		cnt--;
		if (i == l) {
			have += "1";
		} else {
			have += "0";
		}
	}

	if (have.size() > 10) return n + 1;
	if (have[0] == '0' && !cnt) return n + 1;
	if (have[0] == '0') {	
		have[0] = '1';
		cnt--;
	}
	if (have[0] != '1' && cnt) {
		have[0] = '1';
		cnt--;
	}
	for (int i = 1; i < (int)have.size(); i++) {
		if (have[i] == '0') continue;
		if (!cnt) break;
		have[i] = '0';
		cnt--;
	}
	ll ans = 0;
	for (auto i : have) {
		ans *= 10;
		ans += i - '0';
		chkmin(ans, n + 1);
	}
	return ans;
}

const int MAXN = 310, MAXC = 11;
int can[MAXN][MAXN][MAXC];

void build() {
	for (int l = 1; l <= len; l++) {
		for (int r = l; r <= min(l + 10, len); r++) {
			for (int c = 0; c <= 10; c++) {
				can[l][r][c] = get(l, r, c);
			}
		}
	}
}

struct par{
	int last, add;
	par() {
		last = -1;
		add = -1;
	}
	par(int _last, int _add) {
		last = _last, add = _add;
	}
};

int dp[MAXN][MAXN];
par p[MAXN][MAXN];

bool check(int max_val) {
	for (int i = 0; i <= len; i++)
		for (int j = 0; j <= k; j++)
			dp[i][j] = n + 1;
	dp[0][0] = 0;
	for (int i = 1; i <= len; i++) {
		for (int cnt = 0; cnt <= min(k, i); cnt++) {
			for (int last = max(0, i - 12); last < i - 1; last++) {
				for (int add = 0; add <= 10; add++) {
					if (add + (s[i - 1] != '+') > cnt) break;
					int x = can[last + 1][i - 1][add];
					if (x > max_val) continue;
					assert(cnt - add - (s[i - 1] != '+') >= 0);
					int fans = dp[last][cnt - add - (s[i - 1] != '+')] + x;
					if (dp[i][cnt] <= fans) continue;
					dp[i][cnt] = fans;
					p[i][cnt] = par(last, add); 
				}
			}
		}
	}
	/*cout << "dp = " << endl;
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= k; j++) {
			cout << (dp[i][j] == n + 1 ? -1 : dp[i][j]) << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "pos = " << endl;
	for (int i = 0; i <= len; i++) {
		for (int j = 0; j <= k; j++) {
			cout << p[i][j].last << " " << p[i][j].add << " | ";
		}
		cout << endl;
	}
	cout << endl;*/

	return dp[len][k] <= n;
}

int max_val;

void calc() {
	int l = -1, r = n + 1;
	while (l < r - 1) {
		int mid = (l + r) / 2;
		if (check(mid)) {
			r = mid;
		} else {
			l = mid;
		}
	}
	if (r == n + 1) no();
	max_val = r;
}

string make(int l, int r, int cnt) {
	l--;
	r--;
	if (l == r) {
		if (s[l] == '0' || cnt > 0) return "0";
		if (s[l] == '+') assert(false);
		string fans = "";
		fans += s[l];
		return fans;
	}
	string have = "";
	for (int i = l; i <= r; i++) {
		if (s[i] != '+') {
			have += s[i];
			continue;	
		}
		if (cnt == 0) assert(false);
		cnt--;
		if (i == l) {
			have += "1";
		} else {
			have += "0";
		}
	}

	if (have.size() > 10) assert(false);
	if (have[0] == '0' && !cnt) assert(false);
	if (have[0] == '0') {	
		have[0] = '1';
		cnt--;
	}
	if (have[0] != '1' && cnt) {
		have[0] = '1';
		cnt--;
	}
	for (int i = 1; i < (int)have.size(); i++) {
		if (have[i] == '0') continue;
		if (!cnt) break;
		have[i] = '0';
		cnt--;
	}
	return have;
}

vector<string> ans;

void make_ans() {
	assert(check(max_val));
	assert(dp[len][k] <= n);
	int pos = len;
	int cnt = k;
	while (pos > 0) {
		int last = p[pos][cnt].last;
		int add = p[pos][cnt].add;
		ans.push_back(make(last + 1, pos - 1, add));
		cnt -= add + (s[pos - 1] != '+');
		pos = last;
	}
	reverse(all(ans));
}

void run() {
	build();
	calc();
	make_ans();
}

void write() {
	for (int i = 0; i < (int)ans.size(); i++) {
		cout << ans[i];
		if (i != (int)ans.size() - 1)
			cout << "+";
	}
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